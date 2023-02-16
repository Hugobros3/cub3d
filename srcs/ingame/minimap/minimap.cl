int get_map(__global int *map, int2 map_size, int2 p)
{
	if (p.x < 0 || p.y < 0 || p.x >= map_size.x || p.y >= map_size.y)
		return (0);
	return (map[p.y * map_size.x + p.x]);
}

float2	rotate2(float2 v, float rot)
{
	return (float2)(v.x * cos(rot) - v.y * sin(rot), v.x * sin(rot) + v.y * cos(rot));
}

int4 draw(float2 uv, __global void *data, int hovered, int clicked, int2 map_size, float2 player_pos, float player_rot)
{
	__global int *map = (__global int *)(data);

	if (distance(uv, (float2)(0.5, 0.5)) >= 0.5)
		return ((int4)(0, 0, 0, 0));
	player_rot = (int)(player_rot) % 360;
	float2 p = rotate2((uv - (float2)(0.5)) / 2, radians(player_rot + 90)) * (float2)(map_size.x) + player_pos;
	int2 map_p = convert_int2(p);


	if (distance(p, player_pos) < 0.5)
		return ((int4)(255,0,0,255));

	if (get_map(map, map_size, map_p) == 0)
		return ((int4)(0,0,0,255));
	if (get_map(map, map_size, map_p) >= 100)
		return ((int4)(0,255,0,255));
	return ((int4)(255,255,255,255));

}

int4 alpha_blend(int4 c, int4 bg)
{
    float alpha = c.w / 255.0f;
    float oneminusalpha = 1 - alpha;

	int4 out;
    out.x = ((c.x * alpha) + (oneminusalpha * bg.x));
    out.y = ((c.y * alpha) + (oneminusalpha * bg.y));
    out.z = ((c.z * alpha) + (oneminusalpha * bg.z));
	out.w = 1;
	return (out);
}

int4 get_pixel(int2 p, int2 screen_size, __global int *img)
{
	int pixel = img[p.y * screen_size.x + p.x];
	int4 col;
	col.w = ((pixel >> 24) & 0xFF);
	col.x = ((pixel >> 16) & 0xFF);
	col.y = ((pixel >> 8) & 0xFF);
	col.z = ((pixel) & 0xFF);
	return (col);
}

__kernel void eval_minimap(__global int * out, int2 screen_size, int hovered, int clicked, __global void *data, int2 map_size, float2 player_pos, float player_rot)
{
	int2 size =	(int2)(get_global_size(0),	get_global_size(1));
	int2 id = 	(int2)(get_global_id(0),	get_global_id(1));

	float2 uv = (float2)(
		(float)(id.x - get_global_offset(0)) / size.x,
		(float)(id.y - get_global_offset(1)) / size.y
	);

	int4 bg = get_pixel(id, screen_size, out);
	int4 col = alpha_blend(draw(uv, data, hovered, clicked, map_size, player_pos, player_rot), bg);
	out[id.y * screen_size.x + id.x] = (((col.w & 0xff) << 24) + ((col.x & 0xff) << 16)
        + ((col.y & 0xff) << 8) + (col.z & 0xff));
}
