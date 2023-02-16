/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:49:43 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 18:38:46 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine_int.h"
#include "mlx_engine.h"

static void	set_alpha(t_game *g)
{
	t_mlxcl_prog	*prog;
	size_t			*local_size;
	size_t			*global_size;
	int				err;

	local_size = (size_t[2]){16, 16};
	global_size = (size_t[2]){g->size.x, g->size.y};
	prog = mlxcl_get_prog(g->cl_data, "mlxe_set_alpha");
	mlxcl_set_arg(prog, 0, sizeof(void *), &g->frame_buffer);
	mlxcl_set_arg(prog, 1, sizeof(t_iv2), &g->size);
	err = clEnqueueNDRangeKernel(g->cl_data->queue, prog->kernel, 2,
			0, global_size, local_size, 0, NULL, NULL);
	mlxcl_check_err(err, "Couldn't enqueue mlxe_set_alpha kernel.\n");
}

static void	render_to_screen(t_game *g)
{
	mlx_clear_window(g->mlx, g->window);
	clFinish(g->cl_data->queue);
	clEnqueueReadBuffer(g->cl_data->queue, g->frame_buffer, CL_FALSE, 0,
		sizeof(int) * vlen2i(g->size), g->intern->render_img->addr, 0,
		NULL, NULL);
	mlx_put_image_to_window(g->mlx, g->window, g->intern->render_img->img,
		0, 0);
	set_alpha(g);
}

static void	exec_coroutines(t_game *g)
{
	t_list		*curr;
	t_list		*next;
	t_coroutine	*c;

	curr = g->intern->coroutines;
	while (curr)
	{
		next = curr->next;
		c = (t_coroutine *)curr->content;
		if (c->update(c))
		{
			if (c->on_end)
				c->on_end(c);
			mlxe_destroy_coroutine(g, c);
		}
		curr = next;
	}
}

static void	mlxe_mainloop2(t_game *g)
{
	pthread_mutex_lock(&g->sychro_mutex);
	update_time(g);
	update_fps_counter(g);
	update_win_name(g);
	update_ui_selection(g);
	exec_loop_hooks(g);
	exec_coroutines(g);
	draw_ui(g->ui_root, g);
	debug_menu_update(g);
	render_to_screen(g);
}

int	mlxe_mainloop(void *data)
{
	t_game			*g;
	t_list			*curr;
	t_iv2			pos;

	g = (t_game *)data;
	mlxe_mainloop2(g);
	ft_lstclear(&g->intern->keys_down_frame, free);
	curr = g->intern->imgs_to_win;
	pos = iv2(0, 0);
	while (curr)
	{
		mlx_put_image_to_window(g->mlx, g->window,
			((t_image *)curr->content)->img, pos.x, pos.y);
		pos.x += ((t_image *)curr->content)->size->x;
		if (pos.x >= g->size.x)
		{
			pos.x = 0;
			pos.y += ((t_image *)curr->content)->size->y;
		}
		curr = curr->next;
	}
	pthread_mutex_unlock(&g->sychro_mutex);
	return (0);
}
