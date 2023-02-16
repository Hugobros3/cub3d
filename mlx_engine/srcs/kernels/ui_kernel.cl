int4 draw(float2 uv, __global void *data, int hovered, int clicked);


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

__kernel void ui_kernel(__global int * out, int2 screen_size, int hovered, int clicked, __global void *data)
{
	int2 size =	(int2)(get_global_size(0),	get_global_size(1));
	int2 id = 	(int2)(get_global_id(0),	get_global_id(1));

	float2 uv = (float2)(
		(float)(id.x - get_global_offset(0)) / size.x,
		(float)(id.y - get_global_offset(1)) / size.y
	);

	int4 bg = get_pixel(id, screen_size, out);
	int4 col = alpha_blend(draw(uv, data, hovered, clicked), bg);
	out[id.y * screen_size.x + id.x] = (((col.w & 0xff) << 24) + ((col.x & 0xff) << 16)
        + ((col.y & 0xff) << 8) + (col.z & 0xff));
}
