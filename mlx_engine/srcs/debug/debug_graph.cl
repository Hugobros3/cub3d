int4 draw(float2 uv, __global float *data, int fps_index, int fps_max)
{
	int i = floor(uv.x * fps_max) + fps_index;
	if (i >= fps_max)
		i -= fps_max;
	
	float v = 1 - data[i] / 400;
	if (uv.y >= v)
		return (int4)(111, 75, 5, 127);
	else
		return (int4)(222, 151, 9, 127);
}