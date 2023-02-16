//#include "colors_defines.h"

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

#define STRIPS_WIDTH 0.1f
#define TILING 10.0f
#define DIR 0.3f

#define WARP_TILING 3
#define WARP_SCALE 0.05f

#define COL1 (float4)(COLOR_EMPTY)/(float4)(3)
#define COL2 (float4)(COLOR_WALL)/(float4)(3)

int4 draw(float2 uv, __global float *data, int hovered, int clicked)
{
	int4 c;
	float useless;
	float t = (*data) / 50;

	float2 pos;
	uv.y += t;
	pos.x = mix(uv.x, uv.y, DIR);
	pos.y = mix(uv.y, 1 - uv.x, DIR);

	pos.x += sin(pos.y * WARP_TILING * M_PI_F * 2) * (WARP_SCALE + sin(t * 10) / 30);
	pos.x *= TILING;

	float v = floor(fract(pos.x, &useless) + 0.5);

	return (convert_int4(mix(COL1, COL2, v)));
}