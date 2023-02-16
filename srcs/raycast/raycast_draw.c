/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:30:21 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 18:36:54 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static void	raycast_draw_kernel_args(void)
{
	mlxcl_set_arg(g_raycast.raycast_draw_prog, 12, sizeof(t_player), &g_player);
	if (g_settings.is_server)
		mlxcl_set_arg(g_raycast.raycast_draw_prog, 17,
			sizeof(t_player), &g_player);
	else
		mlxcl_set_arg(g_raycast.raycast_draw_prog, 17,
			sizeof(t_player), &g_player);
}

void	raycast_draw(void)
{
	raycast_draw_kernel_args();
	mlxcl_exec_kernel2(g_game, g_raycast.raycast_draw_prog,
		iv2(16, 16), g_game->size);
	clFinish(g_game->cl_data->queue);
}
