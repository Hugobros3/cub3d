int4 draw(float2 uv, __global void *data, int hovered, int clicked)
{
	if (clicked)
		return (int4)(100, 100, 100, 255);
	if (hovered)
		return (int4)(200, 200, 200, 255);

	return (int4)(255);

}