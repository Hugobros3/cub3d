typedef struct __attribute__((packed)) s_slider_info
{
	int4	c1;
	int4	c2;
	float	handle_size;
	float	border_size;
	float	line_size;
}	t_slider_info;

int4 draw(float2 uv, __global t_slider_info *infos, int hovered, int clicked)
{
	float2 uv2 = (float2)(uv.x, uv.y*(infos->border_size * 2) + (0.5 - (infos->border_size)));
	if (uv.x < infos->border_size && distance(uv2, (float2)(infos->border_size, 0.5)) <= infos->border_size)
		return infos->c1;
	if (uv.x > 1 - infos->border_size && distance(uv2, (float2)(1 - infos->border_size, 0.5)) <= infos->border_size)
		return infos->c1;

	if (uv.y > 0.5 - infos->line_size/2 && uv.y < 0.5 + infos->line_size/2)
		return infos->c2;

	return (int4)(0);

}