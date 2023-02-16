#define BRIGHTNESS (float3)(0.5, 0.5, 0.5)

typedef struct __attribute__ ((packed)) s_tris
{
	float4	p3d1;
	float4	p3d2;
	float4	p3d3;
	float4	world1;
	float4	world2;
	float4	world3;
	float4	normal1;
	float4	normal2;
	float4	normal3;
	float2	p1;
	float2	p2;
	float2	p3;
	float2	tex1;
	float2	tex2;
	float2	tex3;
	float2	bbox_min;
	float2	bbox_max;
	float	w1;
	float	w2;
	float	w3;
	int		rendered;
}	t_tris;

typedef struct __attribute__ ((packed)) s_light
{
	float4	pos;
	float4	col;
	float4	dir;
	float	radius;
	float	size;
	int		is_spotlight;
}	t_light;

__constant sampler_t uv_sampler = CLK_NORMALIZED_COORDS_TRUE | CLK_ADDRESS_CLAMP
	| CLK_FILTER_NEAREST;

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


int4	apply_lighting(float4 in_c, t_tris tri, __global t_light *lights, int lights_count, float3 w)
{
	float3 wp;
	wp.x = w.x * tri.world1.x + w.y * tri.world2.x + w.z * tri.world3.x;
	wp.y = w.x * tri.world1.y + w.y * tri.world2.y + w.z * tri.world3.y;
	wp.z = w.x * tri.world1.z + w.y * tri.world2.z + w.z * tri.world3.z;

	float3 norm;
	norm.x = w.x * tri.normal1.x + w.y * tri.normal2.x + w.z * tri.normal3.x;
	norm.y = w.x * tri.normal1.y + w.y * tri.normal2.y + w.z * tri.normal3.y;
	norm.z = w.x * tri.normal1.z + w.y * tri.normal2.z + w.z * tri.normal3.z;
	norm = normalize(norm);

	in_c /= 255.0f;
	float3 value = BRIGHTNESS;
	for (int i = 0; i < lights_count; i++)
	{
		t_light l = lights[i];
		l.pos = (float4)(l.pos.x, 1 - l.pos.y, l.pos.z, l.pos.w);
		float3 light_dir = normalize(wp - l.pos.xyz);
		//float up_rot = mix(135.0f, 225.0f, inverse_lerp(-1.5f, 1.5f, p.up_rot)) / 360;
		float theta = degrees(acos(dot(light_dir, normalize(-l.dir.xyz))));
		if (theta > l.radius)
			continue ;

		//float3 light_dir = normalize(l.pos.xyz - wp);
		float diff = max(dot(norm, -light_dir), 0.0f);
		float3 diffuse = diff * l.col.xyz;

		float len3D = distance(l.pos.xyz, wp);
		float val = clamp(pow((l.size - len3D) / l.size, (float)0.7), (float)0.0, (float)1.0);
		value += l.col.xyz * val;

		in_c.xyz *= diffuse;
	}
	in_c.xyz *= value;
	return (convert_int4(in_c * 255));
}


float edgeFunction(float2 a, float2 b, float2 c) 
{
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

__kernel void draw_tris(int2 proj_scale, __global t_tris *tris, image2d_t tex, __global float *depth_buf,
					__global int *out, int2 out_size, int2 start, int2 end, __global float *dists_buffer, float sp_dist,
					__global t_light *lights, int lights_count)
{
	int i = get_global_id(0);
	if (!tris[i].rendered)
		return ;
	float area = edgeFunction(tris[i].p1, tris[i].p2, tris[i].p3);

	float2	draw_start = mix(convert_float2(start), convert_float2(end), tris[i].bbox_min / convert_float2(proj_scale));
	float2	draw_end = mix(convert_float2(start), convert_float2(end), tris[i].bbox_max / convert_float2(proj_scale));

	int x = ceil(draw_start.x);
	int y = ceil(draw_start.y);

	while (x < ceil(draw_end.x) && x < out_size.x && x >= 0)
	{
		y = (int)draw_start.y;
		if (x < 0 || x >= out_size.x || sp_dist > dists_buffer[x])
		{
			x++;
			continue ;
		}

		while (y < ceil(draw_end.y) && y < out_size.y && y >= 0)
		{
			int2 xy = (int2)(
				mix(tris[i].bbox_min.x, tris[i].bbox_max.x, inverse_lerp(draw_start.x, draw_end.x, (float)x)),
				mix(tris[i].bbox_min.y, tris[i].bbox_max.y, inverse_lerp(draw_start.y, draw_end.y, (float)y))
			);

			float2 p2 = (float2)(xy.x + 0.5, xy.y + 0.5);
			float3 w = (float3)(
				edgeFunction(tris[i].p3, tris[i].p1, p2), 
				edgeFunction(tris[i].p2, tris[i].p3, p2), 
				edgeFunction(tris[i].p1, tris[i].p2, p2)	
			);
			if (w.x >= 0 && w.y >= 0 && w.z >= 0)
			{
				int d_buff_index =	xy.y * (int)proj_scale.x + xy.x;
				int out_index = y * out_size.x + x;

				float2 t1 = tris[i].tex1;
				float2 t2 = tris[i].tex2;
				float2 t3 = tris[i].tex3;

				w.x /= area;
				w.y /= area;
				w.z /= area;
				float2	uv;
				uv.x = w.x * t1.x + w.y * t2.x + w.z * t3.x;
				uv.y = w.x * t1.y + w.y * t2.y + w.z * t3.y;
				uv.y = 1 - uv.y;
				float tex_w = w.x * tris[i].w1 + w.y * tris[i].w2 + w.z * tris[i].w3;
				if (tex_w >= depth_buf[d_buff_index])
				{
					int4 c = sample_img(tex, uv, uv_sampler);
					//c = apply_lighting(convert_float4(c), tris[i], lights, lights_count, w);
						out[out_index] = (((c.w & 0xff) << 24) + ((c.x & 0xff) << 16)
							+ ((c.y & 0xff) << 8) + (c.z & 0xff));
					depth_buf[d_buff_index] = tex_w;
				}
			}
			y++;
		}
		x++;
	}
}