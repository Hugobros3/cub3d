#define MAX_DIST 100
#define BRIGHTNESS (float3)(0.2, 0.2, 0.2)

//a changer
#define HEIGHT 0.5
#define UP_ROT 0

typedef struct __attribute__((packed)) s_player
{
	float2	pos;
	float	rot;
	float	height;
	float	fov;
	float	up_rot;
}	t_player;

typedef struct __attribute__((packed)) s_ray_data
{
	float2	ray;
	float2	ray_dir;
	float	ray_angle;
	int		side;
	int		door;
}	t_ray_data;

typedef struct s_door
{
	float2	pos;
	float	open_amount;
	int		flipped;
}	t_door;

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

float2	send_ray(t_player p, float2 rayd_dir, int2 map_size, __global int * map, int *side, int *door, __global t_door *doors_array)
{
		float2 ray_start = p.pos;
		float2 ray_step = (float2)(
			sqrt(1 + (rayd_dir.y / rayd_dir.x) * (rayd_dir.y / rayd_dir.x)),
			sqrt(1 + (rayd_dir.x / rayd_dir.y) * (rayd_dir.x / rayd_dir.y))
		);
		int2 map_pos = convert_int2(floor(ray_start));
		float2 ray_length;
		int2 step;

		int2 rayd_dir_over_zero = (int2)(rayd_dir.x < 0, rayd_dir.y < 0);

		ray_length.x = rayd_dir_over_zero.x * ((ray_start.x - (float)(map_pos.x)) * ray_step.x)
						 + !rayd_dir_over_zero.x * (((float)(map_pos.x + 1) - ray_start.x) * ray_step.x);
		ray_length.y = rayd_dir_over_zero.y * ((ray_start.y - (float)(map_pos.y)) * ray_step.y)
						 + !rayd_dir_over_zero.y * (((float)(map_pos.y + 1) - ray_start.y) * ray_step.y);
		step.x = rayd_dir_over_zero.x * -1 + !rayd_dir_over_zero.x * 1;
		step.y = rayd_dir_over_zero.y * -1 + !rayd_dir_over_zero.y * 1;


		int stop = false;
		float dist = 0.0f;
		while (stop != 1 && dist < MAX_DIST)
		{
			int2	condition = (int2)(ray_length.x < ray_length.y);
			condition.y = !condition.y;

			dist = (ray_length.x * (float)condition.x) + (ray_length.y * (float)condition.y);
			*side = (1 * condition.x);
			map_pos += step * condition;
			ray_length += ray_step * convert_float2(condition);

			stop = (map_pos.x >= 0 && map_pos.x < map_size.x && map_pos.y >= 0 && map_pos.y < map_size.y);
			if (stop && (map[map_pos.y * map_size.x + map_pos.x] >= 100)) // >= 100
			{
				int index = map[map_pos.y * map_size.x + map_pos.x] - 100;
				float2 d1, d2; 
				float2 r1, r2;
				float2 result;
				if (doors_array[index].flipped)
				{
					d1.x = map_pos.x + 0.5;
					d1.y = map_pos.y + doors_array[index].open_amount;
					d2.x = map_pos.x + 0.5;
					d2.y = map_pos. y + 1;
				}
				else
				{
					d1.x = map_pos.x + doors_array[index].open_amount;
					d1.y = map_pos.y + 0.5;
					d2.x = map_pos.x + 1;
					d2.y = map_pos. y + 0.5;
				}
				r1 = ray_start;
				r2 = ray_start + rayd_dir * (map_size.x + map_size.y);
				if (get_line_intersection(d1, d2, r1, r2, &result))
				{
					*door = index + 1;
					return (result);
				}
			}
			stop = stop && (map[map_pos.y * map_size.x + map_pos.x] == 0);
		}
		return (ray_start + rayd_dir * dist);
}

__kernel void raycast(__global float *out, __global t_ray_data *ray_data, __global int *map, int2 size_map, t_player p, __global t_door *doors_array)//global float array doors
{
	int size = get_global_size(0);
    int x = get_global_id(0);
	float increment_angle = p.fov / size;

	float ray_angle = radians((p.rot - p.fov / 2) + increment_angle * x);
	float2 dir = (float2)(cos(ray_angle), sin(ray_angle));

	int side2;
	int door;
	door = 0;
	float2 ray = send_ray(p, dir, size_map, map, &side2, &door, doors_array);

	int side =	((side2 && dir.x <= 0) * 0) +
				((side2 && dir.x > 0) * 1) +
				((!side2 && dir.y > 0) * 2) +
				((!side2 && dir.y <= 0) * 3);

	float dist = (distance(p.pos, ray) + 0.00001);
	dist *= cos(ray_angle - radians(p.rot));
	out[x] = dist;
	ray_data[x] = (t_ray_data){.side = side, .ray = ray, .ray_dir = dir, .ray_angle = ray_angle, .door = door};
}
