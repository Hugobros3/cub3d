/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:07:25 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 15:11:24 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_mouse_pos(t_iv2 mouse_pos)
{
	if (g_settings.mouse_lock)
	{
		if (mouse_pos.x <= 5)
			mlxe_mouse_move(g_game, iv2(g_game->size.x - 20, mouse_pos.y));
		if (mouse_pos.x >= g_game->size.x - 5)
			mlxe_mouse_move(g_game, iv2(20, mouse_pos.y));
		if (mouse_pos.y <= 5)
			mlxe_mouse_move(g_game, iv2(mouse_pos.x, g_game->size.y - 20));
		if (mouse_pos.y >= g_game->size.y - 5)
			mlxe_mouse_move(g_game, iv2(mouse_pos.y, 20));
	}
}

void	handle_mouse_control(void)
{
	static t_iv2	last_mouse_pos = (t_iv2){-1, -1};
	t_iv2			mouse_pos;
	int				x_move;
	int				y_move;

	if (!g_settings.mouse_controls)
		return ;
	if (last_mouse_pos.x < 0 && last_mouse_pos.y < 0)
	{
		last_mouse_pos = mlxe_get_mouse_pos(g_game);
		return ;
	}
	mouse_pos = mlxe_get_mouse_pos(g_game);
	x_move = last_mouse_pos.x - mouse_pos.x;
	g_player.rot -= (float)x_move * g_game->d_time * g_settings.mouse_sensi;
	y_move = last_mouse_pos.y - mouse_pos.y;
	g_player.up_rot -= (float)y_move * g_game->d_time
		* g_settings.mouse_sensi / 20;
	update_mouse_pos(mouse_pos);
	last_mouse_pos = mlxe_get_mouse_pos(g_game);
}
