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

__kernel void mlxe_set_alpha(__global int * out, int2 screen_size)
{
	int2 size =	(int2)(get_global_size(0),	get_global_size(1));
	int2 id = 	(int2)(get_global_id(0),	get_global_id(1));

	float2 uv = (float2)(
		(float)(id.x - get_global_offset(0)) / size.x,
		(float)(id.y - get_global_offset(1)) / size.y
	);

	int4 col = get_pixel(id, screen_size, out);
	col.x = 0;
	col.y = 0;
	col.z = 0;
	out[id.y * screen_size.x + id.x] = (((col.w & 0xff) << 24) + ((col.x & 0xff) << 16)
        + ((col.y & 0xff) << 8) + (col.z & 0xff));
}