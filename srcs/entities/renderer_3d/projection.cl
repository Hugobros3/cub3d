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

float3 rot3d(float3 p, float3 rot)
{
    float cosa = cos(rot.z);
    float sina = sin(rot.z);

    float cosb = cos(rot.y);
    float sinb = sin(rot.y);

    float cosc = cos(rot.x);
    float sinc = sin(rot.x);

    float Axx = cosa*cosb;
    float Axy = cosa*sinb*sinc - sina*cosc;
    float Axz = cosa*sinb*cosc + sina*sinc;

    float Ayx = sina*cosb;
    float Ayy = sina*sinb*sinc + cosa*cosc;
    float Ayz = sina*sinb*cosc - cosa*sinc;

    float Azx = -sinb;
    float Azy = cosb*sinc;
    float Azz = cosb*cosc;

	float3 out;
    out.x = Axx*p.x + Axy*p.y + Axz*p.z;
    out.y = Ayx*p.x + Ayy*p.y + Ayz*p.z;
    out.z = Azx*p.x + Azy*p.y + Azz*p.z;
	return (out);
}

int is_triangle_rendered(float3 p1, float3 p2, float3 p3)
{
	float3 l1 = p2 - p1;
	float3 l2 = p3 - p1;
	float3 normal = cross(l1,l2);
	float l = sqrt(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
	normal.x /= l; normal.y /= l; normal.z /= l;
	float3 cam = (float3)(0, 0, 0);
	float3 p_cam = p1 - cam;
	return (normal.x * (p1.x - cam.x) +
			   normal.y * (p1.y - cam.y) +
			   normal.z * (p1.z - cam.z) < 0);
}

float4 matrix_mult(float4 v, float *mat)
{
	float4 ret;
	ret.x = v.x * mat[0] + v.y * mat[1] + v.z * mat[2] + v.w * mat[3];
	ret.y = v.x * mat[4] + v.y * mat[5] + v.z * mat[6] + v.w * mat[7];
	ret.z = v.x * mat[8] + v.y * mat[9] + v.z * mat[10] + v.w * mat[11];
	ret.w = v.x * mat[12] + v.y * mat[13] + v.z * mat[14] + v.w * mat[15];
	return (ret);
}

float4  project_v(float3 v, int2 proj_size, float *mat)
{
	float4 ret = matrix_mult((float4)(v.x, v.y, v.z, 1), mat);
	if(ret.w != 0)
	{
		float d = ret.w;
		ret.x /= d;
		ret.y /= d;
		ret.z /= d;
	}
	return (ret);
}

float3	get_normal(float3 p1, float3 p2, float3 p3, float e_rot)
{
	p1 = rot3d(p1, (float3)(0, e_rot, 0));
	p2 = rot3d(p2, (float3)(0, e_rot, 0));
	p3 = rot3d(p3, (float3)(0, e_rot, 0));

	float3 l1 = p2 - p1;
	float3 l2 = p3 - p1;
	float3 normal = normalize(cross(l1,l2));
	return (normal);
}

__kernel void projection(int2 proj_scale, float4 translation, float4 rotation, __global t_tris *triangles, float4 world_pos, float e_rot,
				int global_size)
{
	int i = get_global_id(0);

	if (i >= global_size)
		return ;

	e_rot = radians(360 - e_rot + 90);
	t_tris tr = triangles[i];
	float3 pp1 = rot3d(tr.p3d1.xyz, rotation.xyz);
	float3 pp2 = rot3d(tr.p3d2.xyz, rotation.xyz);
	float3 pp3 = rot3d(tr.p3d3.xyz, rotation.xyz);
	triangles[i].world1 = rot3d(tr.p3d1.xyz, (float3)(0, e_rot, 0)).xyzz + world_pos;
	triangles[i].world2 = rot3d(tr.p3d2.xyz, (float3)(0, e_rot, 0)).xyzz + world_pos;
	triangles[i].world3 = rot3d(tr.p3d3.xyz, (float3)(0, e_rot, 0)).xyzz + world_pos;

	float3 normal = get_normal(tr.p3d1.xyz, tr.p3d2.xyz, tr.p3d3.xyz, e_rot);

	pp1 += translation.xyz;
	pp2 += translation.xyz;
	pp3 += translation.xyz;

	if (!is_triangle_rendered(pp1, pp2, pp3))
	{
		triangles[i].rendered = 0;
		return ;
	}
	
	float mat[16];
	float view_angle = 90;
	float fov = 1.0 / tan(view_angle * 0.5 / 180 * M_PI_F);
	float ratio = proj_scale.y / proj_scale.y;
	float far = 1000;
	float near = 0.1;

	#pragma unroll
	for (int i = 0; i < 16; i++)
		mat[i] = 0;

	mat[0] = fov * ratio;
	mat[5] = fov;
	mat[10] = far/(far-near);
	mat[11] = 1;
	mat[14] = (-far * near)/(far-near);

	float4 p1 = project_v(pp1, proj_scale, mat);
	float4 p2 = project_v(pp2, proj_scale, mat);
	float4 p3 = project_v(pp3, proj_scale, mat);

	float3 ip1 = (float3)((p1.x + 1) * 0.5 * proj_scale.x, (p1.y + 1) * 0.5 * proj_scale.y, p1.z);
	float3 ip2 = (float3)((p2.x + 1) * 0.5 * proj_scale.x, (p2.y + 1) * 0.5 * proj_scale.y, p2.z);
	float3 ip3 = (float3)((p3.x + 1) * 0.5 * proj_scale.x, (p3.y + 1) * 0.5 * proj_scale.y, p3.z);

	float3 mi = min(ip1, ip2);
	mi = min(mi, ip3);
	float3 ma = max(ip1, ip2);
	ma = max(ma, ip3);

//	triangles[i].normal1 = tr.normal1;
//	triangles[i].normal2 = tr.normal2;
//	triangles[i].normal3 = tr.normal3;

	triangles[i].normal1 = normal.xyzz;
	triangles[i].normal2 = normal.xyzz;
	triangles[i].normal3 = normal.xyzz;

	triangles[i].p1 = ip1.xy;
	triangles[i].p2 = ip2.xy;
	triangles[i].p3 = ip3.xy;
	triangles[i].tex1 = tr.tex1;
	triangles[i].tex2 = tr.tex2;
	triangles[i].tex3 = tr.tex3;
	triangles[i].w1 = p1.w;
	triangles[i].w2 = p2.w;
	triangles[i].w3 = p3.w;
	triangles[i].bbox_min = mi.xy;
	triangles[i].bbox_max = ma.xy;
	triangles[i].rendered = 1;
}

