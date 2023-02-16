/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:20:41 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 18:39:38 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe_ui.h"

static void	update_ui_data(t_ui *ui, t_game *g)
{
	if (!ui->eval)
		return ;
	if (!ui->data_buffer && ui->data && ui->data_size > 0)
		ui->data_buffer = mlxcl_create_buffer(g->cl_data,
				CL_RD, ui->data_size, ui->data);
	if (ui->update)
		ui->update(ui);
	if (ui->data_buffer && ui->data && ui->write_data_each_frame)
		mlxcl_write_buffer(g->cl_data, ui->data_buffer,
			ui->data_size, ui->data);
}

static void	actual_draw_ui(t_ui *ui, t_game *g)
{
	int		err;
	t_v2	size;
	t_v2	p;

	update_ui_data(ui, g);
	p = ui->pos;
	size = ui->size;
	p = mult2(p, iv2v2(g->size));
	size = mult2(size, iv2v2(g->size));
	mlxcl_set_arg(ui->eval, 0, sizeof(void *), &g->frame_buffer);
	mlxcl_set_arg(ui->eval, 1, sizeof(t_iv2), &g->size);
	mlxcl_set_arg(ui->eval, 2, sizeof(int), &ui->hovered);
	mlxcl_set_arg(ui->eval, 3, sizeof(int), &ui->clicked);
	mlxcl_set_arg(ui->eval, 4, sizeof(void *), &ui->data_buffer);
	err = clEnqueueNDRangeKernel(
			g->cl_data->queue, ui->eval->kernel, 2,
			(size_t[2]){(int)p.x, (int)p.y},
			(size_t[2]){(int)size.x - ((int)size.x % 8),
			(int)size.y - ((int)size.y % 8)},
			(size_t[2]){8, 8}, 0, NULL, NULL);
	mlxcl_check_err(err, "Couldn't enqueue UI kernel. (global_size: %lu %lu)\n",
		(int)size.x - ((int)size.x % 8), (int)size.y - ((int)size.y % 8));
}

void	draw_ui(t_ui *ui, t_game *g)
{
	t_list	*curr;
	t_ui	*curr_ui;

	if (ui->active == FALSE)
		return ;
	if (ui->eval)
		actual_draw_ui(ui, g);
	curr = ft_lstlast(ui->childs);
	while (curr)
	{
		curr_ui = (t_ui *)curr->content;
		draw_ui(curr_ui, g);
		curr = curr->prev;
	}
}
