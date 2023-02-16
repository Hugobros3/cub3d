/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:41:09 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 18:36:49 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	raycast_cleanup(void)
{
	if (!g_settings.ingame_initialized)
		return ;
	clReleaseMemObject(g_raycast.dists_buffer);
	clReleaseMemObject(g_raycast.map_buffer);
	clReleaseMemObject(g_raycast.ray_data_buffer);
	clReleaseMemObject(g_raycast_textures.no);
	clReleaseMemObject(g_raycast_textures.so);
	clReleaseMemObject(g_raycast_textures.ea);
	clReleaseMemObject(g_raycast_textures.we);
	clReleaseMemObject(g_raycast_textures.door);
}
