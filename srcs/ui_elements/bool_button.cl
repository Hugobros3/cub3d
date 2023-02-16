typedef struct __attribute__((packed)) s_boolbutton_info
{
	int4	c1;
	int4	c2;
	int		v;
	void	*p1;
	void	*p2;
}	t_boolbutton_info;

int4 draw(float2 uv, __global t_boolbutton_info *infos, int hovered, int clicked)
{
	float h = 1;

	if (distance(uv, (float2)(0.5, 0.5)) > 0.5)
		return ((int4)(0));
	if (hovered)
		h = 0.6;
	if (clicked)
		h = 0.4;
	int4 c1 = (int4)(
		(float)infos->c1.x * h,
		(float)infos->c1.y * h,
		(float)infos->c1.z * h,
		255);
	int4 c2 = (int4)(
		(float)infos->c2.x * h,
		(float)infos->c2.y * h,
		(float)infos->c2.z * h,
		255);
	if (infos->v && distance(uv, (float2)(0.5, 0.5)) < 0.2)
		return (c1);
	return (c2);
}