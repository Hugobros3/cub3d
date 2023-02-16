__constant sampler_t uv_sampler = CLK_NORMALIZED_COORDS_TRUE | CLK_ADDRESS_CLAMP
| CLK_FILTER_NEAREST;

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

__kernel void mlxe_eval_img(__global int * out, int2 screen_size, int hovered, int clicked, image2d_t img)
{
	int2 size =	(int2)(get_global_size(0),	get_global_size(1));
	int2 id = 	(int2)(get_global_id(0),	get_global_id(1));

	float2 uv = (float2)(
		(float)(id.x - get_global_offset(0)) / size.x,
		(float)(id.y - get_global_offset(1)) / size.y
	);

	int4 bg = get_pixel(id, screen_size, out);
	int4 sampled = sample_img(img, uv, uv_sampler);
	if (clicked)
	{
		sampled.x = sampled.x / 3;
		sampled.y = sampled.y / 3;
		sampled.z = sampled.z / 3;
	}
	else if (hovered)
	{
		sampled.x = sampled.x / 2;
		sampled.y = sampled.y / 2;
		sampled.z = sampled.z / 2;
	}
	int4 col = alpha_blend(sampled, bg);
	out[id.y * screen_size.x + id.x] = (((col.w & 0xff) << 24) + ((col.x & 0xff) << 16)
        + ((col.y & 0xff) << 8) + (col.z & 0xff));
}
