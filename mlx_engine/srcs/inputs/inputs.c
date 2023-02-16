/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:39:07 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 00:35:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine_int.h"
#include "mlx_engine.h"

#ifdef LINUX

t_iv2	mlxe_get_mouse_pos(t_game *g)
{
	t_iv2	p;

	mlx_mouse_get_pos(g->mlx, g->window, &p.x, &p.y);
	return (p);
}
#else

t_iv2	mlxe_get_mouse_pos(t_game *g)
{
	t_iv2	p;

	mlx_mouse_get_pos(g->window, &p.x, &p.y);
	return (p);
}

#endif

int	mouse_pressed(int keycode, int x, int y, void *g)
{
	t_game	*game;

	(void)x;
	(void)y;
	game = (t_game *)g;
	if (keycode == 1)
	{
		if (game->intern->hovered_ui)
		{
			game->intern->hovered_ui->clicked = TRUE;
			if (game->intern->hovered_ui->on_click)
				game->intern->hovered_ui->on_click(game,
					game->intern->hovered_ui);
		}
		return (0);
	}
	return (0);
}

int	mouse_released(int keycode, int x, int y, void *g)
{
	t_game	*game;

	(void)x;
	(void)y;
	game = (t_game *)g;
	if (keycode == 1)
	{
		if (game->intern->hovered_ui)
		{
			game->intern->hovered_ui->clicked = FALSE;
			if (game->intern->hovered_ui->on_release)
				game->intern->hovered_ui->on_release(game,
					game->intern->hovered_ui);
		}
		return (0);
	}
	return (0);
}

void	init_inputs(t_game *g)
{
	mlx_hook(g->window, 2, (1L << 0), key_press, g);
	mlx_hook(g->window, 3, (1L << 1), key_release, g);
	mlx_hook(g->window, 4, (1L << 2), mouse_pressed, g);
	mlx_hook(g->window, 5, (1L << 3), mouse_released, g);
}
