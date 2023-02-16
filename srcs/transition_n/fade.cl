int4 draw(float2 uv, __global float *f)
{
	return (convert_int4((float4)(0, 0, 0, mix(0.0f, 255.0f, *f))));
}