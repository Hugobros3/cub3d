/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:36:04 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 18:36:57 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycast.h"

t_raycast			g_raycast;
t_raycast_textures	g_raycast_textures;

void	raycast(void)
{
	clEnqueueWriteBuffer(g_game->cl_data->queue, g_raycast.doors_buffer,
		CL_TRUE, 0, sizeof(t_door) * g_map.doors_size,
		g_map.doors, 0, NULL, NULL);
	raycast_dists();
	raycast_draw();
}
