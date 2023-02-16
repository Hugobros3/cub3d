/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_menu_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:23:06 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 19:30:24 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_menu.h"
#ifdef DEBUG

static void	draw_fps_graph(t_game *g, t_iv2 *offset)
{
	t_v2			p;
	t_v2			size;
	t_mlxcl_prog	*prog;
	int				err;

	size = v2(300, 100);
	p = iv2v2(*offset);
	clEnqueueWriteBuffer(g->cl_data->queue, g->intern->debug_m.graph_data,
		TRUE, 0, sizeof(float) * FPS_COUNTER_MAX, g->intern->average_fps,
		0, NULL, NULL);
	prog = g->intern->debug_m.graph;
	mlxcl_set_arg(prog, 0, sizeof(void *), &g->frame_buffer);
	mlxcl_set_arg(prog, 1, sizeof(t_iv2), &g->size);
	mlxcl_set_arg(prog, 2, sizeof(int), &g->intern->fps_index);
	mlxcl_set_arg(prog, 3, sizeof(int), &(int){FPS_COUNTER_MAX});
	mlxcl_set_arg(prog, 4, sizeof(void *), &g->intern->debug_m.graph_data);
	err = clEnqueueNDRangeKernel(g->cl_data->queue, prog->kernel, 2,
			(size_t[2]){(int)p.x, (int)p.y},
			(size_t[2]){(int)size.x - ((int)size.x % 8),
			(int)size.y - ((int)size.y % 8)},
			(size_t[2]){8, 8},
			0, NULL, NULL);
	mlxcl_check_err(err, "Couldn't enqueue UI kernel. (global_size: %lu %lu)\n",
		(int)size.x - ((int)size.x % 8), (int)size.y - ((int)size.y % 8));
	offset->y += size.y;
}

static void	render_text(t_game *g, char *text, t_iv2 *offset)
{
	t_image	*img;
	t_iv2	p;
	t_v2	uv;
	t_iv2	uv2;

	img = mlxe_render_text(g, g->intern->debug_m.font,
			text, new_color(222, 151, 9, 255));
	p = *offset;
	while (p.y - offset->y < img->size->y)
	{
		uv = ft_invlerp2(iv2v2(*offset),
				add2(iv2v2(*(img->size)),
					iv2v2(*offset)), iv2v2(p));
		uv2 = v2iv2(mult2(uv, iv2v2(*(img->size))));
		clEnqueueWriteBuffer(g->cl_data->queue, g->frame_buffer, TRUE,
			(p.y * g->size.x + p.x) * sizeof(int), img->size->x * sizeof(int),
			((int *)img->addr) + (uv2.y * img->size->x + uv2.x), 0, NULL, NULL);
		p.y++;
	}
	offset->y += img->size->y + 10;
	free_img(img, g->mlx);
}

void	debug_menu_update(t_game *g)
{
	t_list			*curr;
	char			*to_render;
	t_debug_entry	*e;
	t_iv2			offset;

	offset.y = 100;
	offset.x = 10;
	draw_fps_graph(g, &offset);
	curr = g->intern->debug_m.entries;
	while (curr)
	{
		e = curr->content;
		to_render = e->get(e->data);
		to_render = ft_str_append(e->name, to_render, 0, 1);
		render_text(g, to_render, &offset);
		free(to_render);
		curr = curr->next;
	}
}
#else

void	debug_menu_update(t_game *g)
{
	(void)g;
}
#endif
