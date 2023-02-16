//#include <colors_defines.h>
//#include <cells_defines.h>

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

typedef struct s_cell
{
	int		tile;
	int		infected;
	int		to_infect;
	int		spawn;
	int		blink;
	int		flag;
	int		is_hole;
	float	t;
}	t_cell;

int4 draw(float2 uv, __global t_cell *cells, int2 cells_size, int hovered, int clicked)
{
	int2	cells_coords = convert_int2(uv * convert_float2(cells_size));
	t_cell	cell = cells[cells_coords.x * cells_size.y + cells_coords.y];
	float4	col;

	if (cell.spawn)
		col = (float4)(COLOR_EMPTY) / (float4)(1.2f);
	else if (cell.infected)
		col = (float4)(COLOR_INFECT2);
	else if (cell.to_infect)
		col = (float4)(COLOR_INFECT1);
	else if (cell.tile != 0)
		col = (float4)(COLOR_EMPTY);
	else
		col = (float4)(COLOR_WALL);

	if (cell.is_hole)
		col = (float4)(COLOR_GOOD1);

	if (cell.blink)
		col = mix(col, (float4)(0, 0, 0, 255), cell.t);

	return (convert_int4(col));
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

__kernel void eval_cells_basic(__global int * out, int2 screen_size, int hovered, int clicked, __global void *data, int2 cells_size)
{
	int2 size =	(int2)(get_global_size(0),	get_global_size(1));
	int2 id = 	(int2)(get_global_id(0),	get_global_id(1));

	float2 uv = (float2)(
		(float)(id.x - get_global_offset(0)) / size.x,
		(float)(id.y - get_global_offset(1)) / size.y
	);

	int4 bg = get_pixel(id, screen_size, out);
	int4 col = alpha_blend(draw(uv, data, cells_size, hovered, clicked), bg);
	out[id.y * screen_size.x + id.x] = (((col.w & 0xff) << 24) + ((col.x & 0xff) << 16)
        + ((col.y & 0xff) << 8) + (col.z & 0xff));
}