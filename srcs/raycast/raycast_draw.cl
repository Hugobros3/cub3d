#define BRIGHTNESS (float3)(0.2, 0.2, 0.2)

__constant sampler_t uv_sampler = CLK_NORMALIZED_COORDS_TRUE | CLK_ADDRESS_REPEAT
| CLK_FILTER_NEAREST;

__constant sampler_t n_sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP | CLK_FILTER_NEAREST;

typedef struct __attribute__((packed)) s_ray_data
{
	float2	ray;
	float2	ray_dir;
	float	ray_angle;
	int		side;
	int		door;
}	t_ray_data;

typedef struct __attribute__((packed)) s_player
{
	float2	pos;
	float	rot;
	float	height;
	float	fov;
	float	up_rot;
}	t_player;

typedef struct __attribute__ ((packed)) s_light
{
	float4	pos;
	float4	col;
	float4	dir;
	float	radius;
	float	size;
	int		is_spotlight;
}	t_light;

typedef struct s_door
{
	float2	pos;
	float	open_amount;
	int		flipped;
}	t_door;

//========================================================================================

float	inverse_lerp(float a, float b, float value)
{
	return ((value - a) / (b - a));
}

int4	sample_img(image2d_t img, float2 uv, sampler_t sampler)
{
	uint4 pixel = read_imageui(img, sampler, uv);
	int4 col;
	col.w = ((pixel.x >> 24) & 0xFF);
	col.x = ((pixel.x >> 16) & 0xFF);
	col.y = ((pixel.x >> 8) & 0xFF);
	col.z = ((pixel.x) & 0xFF);
	return (col);
}

//========================================================================================

float3 reflect( float3 i, float3 n)
{
	return i - 2 * n * dot(n,i);
}

char get_line_intersection(float2 p0, float2 p1, float2 p2, float2 p3, float2 *i)
{
    float2 s1, s2;
    s1.x = p1.x - p0.x;     s1.y = p1.y - p0.y;
    s2.x = p3.x - p2.x;     s2.y = p3.y - p2.y;

    float s, t;
    s = (-s1.y * (p0.x - p2.x) + s1.x * (p0.y - p2.y)) / (-s2.x * s1.y + s1.x * s2.y);
    t = ( s2.x * (p0.y - p2.y) - s2.y * (p0.x - p2.x)) / (-s2.x * s1.y + s1.x * s2.y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        i->x = p0.x + (t * s1.x);
        i->y = p0.y + (t * s1.y);
        return 1;
	}

    return 0; // No collision
}

void	apply_single_light(float3 world_pos, float3 normal, float3 direct, t_light l, int2 map_size, __global int *map, float3 *value, __global t_door *doors)
{
	l.pos = (float4)(l.pos.x, 1 - l.pos.y, l.pos.z, l.pos.w);
	float3 light_dir = normalize(world_pos - l.pos.xyz);
	//float up_rot = mix(135.0f, 225.0f, inverse_lerp(-1.5f, 1.5f, p.up_rot)) / 360;
	float theta = degrees(acos(dot(light_dir, normalize(-l.dir.xyz))));
	if (theta > l.radius)
		return ;

	float3 start = world_pos.xzy;
	float3 end = l.pos.xzy;
	float len2D = distance(start.xy, end.xy);
	if (len2D > l.size)
		return ;
	float2 dir = (end.xy - start.xy) / len2D;

	if (dir.x == 0.0 || dir.y == 0.0)
		return ;
	float2 offset = start.xy + (normal.xz * (float)0.0001);
	float rad = len2D + (float)0.001;

	int2 pos = convert_int2(offset);
	int2 steps = convert_int2(sign(dir));

	float u1;
	float2 tDelta = (float2)(steps.x == 0 ? 1000.0 : steps.x / dir.x, steps.y == 0 ? 1000.0 : steps.y / dir.y);
	float2 tMax = (float2)(tDelta.x * (steps.x > 0 ? 1.0 - fract(offset.x, &u1) : fract(offset.x, &u1)), tDelta.y * (steps.y > 0 ? 1.0 - fract(offset.y, &u1) : fract(offset.y, &u1)));

	bool stop = false;
	for (int j = 0; j < 30; j++) {
		if ((map[pos.y * map_size.x + pos.x] >= 100)) // >= 100
		{
			int index = map[pos.y * map_size.x + pos.x] - 100;
			float2 d1, d2; 
			float2 r1, r2;
			float2 result;
			if (doors[index].flipped)
			{
				d1.x = pos.x + 0.5;
				d1.y = pos.y + doors[index].open_amount;
				d2.x = pos.x + 0.5;
				d2.y = pos. y + 1;
			}
			else
			{
				d1.x = pos.x + doors[index].open_amount;
				d1.y = pos.y + 0.5;
				d2.x = pos.x + 1;
				d2.y = pos. y + 0.5;
			}
			r1 = start.xy;
			r2 = start.xy + dir * (map_size.x + map_size.y);
			if (get_line_intersection(d1, d2, r1, r2, &result))
			{
				stop = true;
				break;
			}
		}
		if (map[pos.y * map_size.x + pos.x] == 0) {
			stop = true;
			break;
		}
		if (tMax.x < tMax.y) {
			if (tMax.x > rad) break;
			pos.x += steps.x;
			tMax.x += tDelta.x;
		} else {
			if (tMax.y > rad) break;
			pos.y += steps.y;
			tMax.y += tDelta.y;
		}
	}

	if (stop)
		return ;

	float len3D = distance(start, end);
	float val = clamp(pow((l.size - len3D) / l.size, (float)2.0), (float)0.0, (float)1.0);
	if (l.is_spotlight)
		*value += l.col.xyz * val * (l.radius - theta) / l.radius;
	else
		*value += l.col.xyz * val;
	*value += pow(
				max(
					dot(direct, reflect(normalize(end - start), normal)),
					(float)0.0),
				(float)10.0)
			* val * l.col.xyz * (float)0.2;
}

int4 apply_lighting(int4 pix, float3 world_pos,
					__global int *map, int2 map_size, float3 normal,
					__global t_light *l, int size, t_player p, t_player flashlight_pl, __global t_door *doors)
{
	float3 direct = normalize(world_pos - (float3)(p.pos.x, p.height, p.pos.y));
	float3 value = BRIGHTNESS;
	for (int i = 0; i < size; i++)
	{
		apply_single_light(world_pos, normal, direct, l[i], map_size, map, &value, doors);
	}

	float3 rgb = convert_float3(pix.xyz);
	pix.xyz = convert_int3(rgb * value);
	pix.xyz = clamp(pix.xyz, (int3)(0, 0, 0), (int3)(255, 255, 255));
	pix.a = 1;
	return (pix);
}

//========================================================================================

int4 draw_wall(image2d_t tex, float y, float2 ray, float3 *world_pos)
{
	int2 tex_size = get_image_dim(tex);
	int	texture_x = (int)floor(tex_size.x * (ray.x + ray.y)) % tex_size.x;		
	float2 coord;
	coord.x = inverse_lerp(0, tex_size.x, texture_x);
	coord.y = y;
	*world_pos = (float3)(ray.x, coord.y, ray.y);
	return (sample_img(tex, coord, uv_sampler));
}

int4 draw_door(image2d_t tex, float y, float2 ray, float3 *world_pos, t_door door)
{
	int2 tex_size = get_image_dim(tex);
	int	texture_x = (int)floor(tex_size.x * (ray.x + ray.y)) % tex_size.x;
	float2 coord;
	coord.x = inverse_lerp(0, tex_size.x, texture_x) - (door.open_amount);
	coord.y = y;
	*world_pos = (float3)(ray.x, coord.y, ray.y);
	return (sample_img(tex, coord, uv_sampler));
}

int4 draw_ceil(image2d_t tex, float4 col, float angle, float2 dir, t_player p, float3 *world_pos)
{
	int2 size = (int2)(get_global_size(0), get_global_size(1));
    int y = get_global_id(1);

	float distance;
	distance = size.y / (2 * (float)(y + size.y - (y * 2)) - size.y - p.up_rot * 600) / (p.fov / 60);
	distance /= (cos(radians(p.rot) - angle)) / (p.fov / 60);
	float2 tile = (dir * distance * (float2)(1 - p.height + 0.5) + p.pos);
	*world_pos = (float3)(tile.x, 0, tile.y);

	int2 tex_size = get_image_dim(tex);
	int texture_x = (int)(floor(tile.x * tex_size.x)) % tex_size.x;
	int texture_y = (int)(floor(tile.y * tex_size.y)) % tex_size.y;

	float2 coord;
	coord.x = texture_x / (float)tex_size.x;
	coord.y = texture_y / (float)tex_size.y;

	float4 c_tex = convert_float4(sample_img(tex, coord / 2, uv_sampler));
	c_tex *= (col / 255.0f);

	return (convert_int4(c_tex));
}

int4 draw_floor(image2d_t tex, float4 col, float angle, float2 dir, t_player p, float3 *world_pos)
{
	int2 size = (int2)(get_global_size(0), get_global_size(1));
    int y = get_global_id(1);

	float distance;
	distance = size.y / (2 * (float)y - size.y + p.up_rot * 600) / (p.fov / 60);
	distance /= (cos(radians(p.rot) - angle)) / (p.fov / 60);
	float2 tile = (dir * distance * (float2)(p.height + 0.5) + p.pos);
	*world_pos = (float3)(tile.x, 1, tile.y);

	int2 tex_size = get_image_dim(tex);
	int texture_x = (int)(floor(tile.x * tex_size.x)) % tex_size.x;
	int texture_y = (int)(floor(tile.y * tex_size.y)) % tex_size.y;

	float2 coord;
	coord.x = texture_x / (float)tex_size.x;
	coord.y = texture_y / (float)tex_size.y;

	float4 c_tex = convert_float4(sample_img(tex, coord / 2, uv_sampler));
	c_tex *= (col / 255.0f);

	return (convert_int4(c_tex));
}

//========================================================================================

__kernel void raycast_draw(__global float *dists, __global t_ray_data *ray_data, __global int *out,
							image2d_t no, image2d_t so, image2d_t ea, image2d_t we,
							image2d_t floor_tex, image2d_t ceil_tex, float4 floor_col, float4 ceil_col,
							image2d_t door_tex, t_player player, __global t_light *lights, int lights_count,
							__global int *map, int2 map_size, t_player flashlight_pl, __global t_door *doors)
{
	int2 p = (int2)(get_global_id(0), get_global_id(1));
	int2 size = (int2)(get_global_size(0), get_global_size(1));

	float h_size_y = size.y / 2;
	float wall_height = floor(h_size_y / dists[p.x]);
	float3 world_pos;
	float3 normal;
	int4 col;

	int w_start = (h_size_y - wall_height * (1 - player.height + 0.5) - player.up_rot * 300);
	int w_end = (h_size_y + wall_height * (player.height + 0.5) - player.up_rot * 300);

	int		side = ray_data[p.x].side;
	float	ray_angle = ray_data[p.x].ray_angle;
	float2	ray = ray_data[p.x].ray;
	float2	dir = ray_data[p.x].ray_dir;
	int		door = ray_data[p.x].door;
	if (p.y < w_start)
	{
		col = draw_ceil(ceil_tex, ceil_col, ray_angle, dir, player, &world_pos);
		normal = (float3)(0, -1, 0);
	}
	else if (p.y >= w_start && p.y <= w_end)
	{
		if (door)
		{
			door -= 1;
			col = draw_door(door_tex, inverse_lerp(w_start, w_end, (float)p.y), ray, &world_pos, doors[door]);
			normal = (float3)(0, 0, 0);//a faire
		}
		else if (side == 0)
		{
			col = draw_wall(no, inverse_lerp(w_start, w_end, (float)p.y), ray, &world_pos);
			normal = (float3)(1, 0, 0);
		}
		else if (side == 1)
		{
			col = draw_wall(so, inverse_lerp(w_start, w_end, (float)p.y), ray, &world_pos);
			normal = (float3)(-1, 0, 0);
		}
		else if (side == 2)
		{
			col = draw_wall(ea, inverse_lerp(w_start, w_end, (float)p.y), ray, &world_pos);
			normal = (float3)(0, 0, -1);
		}
		else
		{
			col = draw_wall(we, inverse_lerp(w_start, w_end, (float)p.y), ray, &world_pos);
			normal = (float3)(0, 0, 1);
		}
	}
	else
	{
		col = draw_floor(floor_tex, floor_col, ray_angle, dir, player, &world_pos);
		normal = (float3)(0, 1, 0);
	}

	col = apply_lighting(col, world_pos, map, map_size, normal, lights, lights_count, player, flashlight_pl, doors);

	out[p.y * size.x + p.x] = (((col.w & 0xff) << 24) + ((col.x & 0xff) << 16)
        + ((col.y & 0xff) << 8) + (col.z & 0xff));
}