//#include "colors_defines.h"
//#include "cells_defines.h"

# define COLOR_WRONG 240, 72, 5, 255
# define COLOR_WHITE 255, 255, 255, 255
# define COLOR_GOOD1 129, 240, 65, 255
# define COLOR_GOOD2 61, 163, 2, 255
# define COLOR_EMPTY 255, 242, 206, 255
# define COLOR_WALL 128, 128, 128, 255
# define COLOR_INFECT1 70, 255, 157, 255
# define COLOR_INFECT2 0, 163, 76, 255
# define COLOR_OK2 16, 31, 163, 255

# define CELL_BORDER 0.01f
# define PREFERED_CELL_SIZE 0.02f

typedef struct s_done_anim
{
	float4	c;
	int2	size;
	float2	p;
	float	d;
}	t_done_anim;

int4	draw(float2 uv, __global t_done_anim *anim)
{
	float2	scaled_uv;

	scaled_uv = uv * convert_float2(anim->size);

	if (distance(scaled_uv, anim->p) < anim->d)
		return (convert_int4(anim->c));
	else
		return ((int4)(0));
}	