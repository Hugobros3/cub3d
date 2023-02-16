/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dists.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 02:27:58 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 15:57:54 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycast.h"

static void	raycast_kernel_args(void)
{
	mlxcl_set_arg(g_raycast.raycast_prog, 4, sizeof(t_player), &g_player);
}

void	raycast_dists(void)
{
	raycast_kernel_args();
	pthread_mutex_lock(&g_raycast.map_buffer_m);
	mlxcl_exec_kernel(g_game, g_raycast.raycast_prog, 16, g_game->size.x);
	pthread_mutex_unlock(&g_raycast.map_buffer_m);
}
