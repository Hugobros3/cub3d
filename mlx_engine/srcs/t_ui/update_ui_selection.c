/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ui_selection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:29:10 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/25 23:46:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe_ui.h"

int	is_left(t_iv2 p0, t_iv2 p1, t_iv2 p2)
{
	return ((p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y));
}

int	is_inside(t_iv2 *points, t_iv2 p)
{
	return (is_left(points[0], points[1], p) > 0
		&& is_left(points[1], points[3], p) > 0
		&& is_left(points[3], points[2], p) > 0
		&& is_left(points[2], points[0], p) > 0);
}

void	compute_corners(t_game *game, t_ui *ui, t_iv2 *out)
{
	t_v2	points[4];
	t_v2	origin;

	points[0].x = ui->pos.x * game->size.x;
	points[0].y = ui->pos.y * game->size.y;
	points[1].x = game->size.x * (ui->size.x + ui->pos.x);
	points[1].y = ui->pos.y * game->size.y;
	points[2].x = ui->pos.x * game->size.x;
	points[2].y = game->size.y * (ui->size.y + ui->pos.y);
	points[3].x = game->size.x * (ui->size.x + ui->pos.x);
	points[3].y = game->size.y * (ui->size.y + ui->pos.y);
	origin = v2((points[0].x + points[3].x) / 2,
			(points[0].y + points[3].y) / 2);
	points[0] = ft_rotate2(points[0], ui->rot, origin);
	points[1] = ft_rotate2(points[1], ui->rot, origin);
	points[2] = ft_rotate2(points[2], ui->rot, origin);
	points[3] = ft_rotate2(points[3], ui->rot, origin);
	out[0] = iv2((int)(points[0].x), (int)(points[0].y));
	out[1] = iv2((int)(points[1].x), (int)(points[1].y));
	out[2] = iv2((int)(points[2].x), (int)(points[2].y));
	out[3] = iv2((int)(points[3].x), (int)(points[3].y));
}

static t_ui	*update_ui_selection_recursive(t_iv2 p, t_game *g, t_ui *ui)
{
	t_iv2	ui_dims[4];
	t_ui	*selected;
	t_ui	*ret;
	t_list	*curr;

	if (!ui->active || !ui->interactable)
		return (NULL);
	selected = NULL;
	compute_corners(g, ui, ui_dims);
	if (is_inside(ui_dims, iv2(p.x, p.y)))
		selected = ui;
	else
		if (g->intern->hovered_ui == ui)
			unselect_ui(g);
	curr = ui->childs;
	while (curr)
	{
		ret = update_ui_selection_recursive(p, g, (t_ui *)curr->content);
		if (ret)
			selected = ret;
		curr = curr->next;
	}
	return (selected);
}

void	update_ui_selection(t_game *game)
{
	t_iv2		p;
	t_ui		*selected;

	p = mlxe_get_mouse_pos(game);
	selected = update_ui_selection_recursive(p, game, game->ui_root);
	if (selected)
	{
		if (game->intern->hovered_ui && selected != game->intern->hovered_ui)
			unselect_ui(game);
		if (game->intern->hovered_ui != selected)
			select_ui(game, selected);
	}
}
