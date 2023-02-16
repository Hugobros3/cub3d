/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 00:33:32 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 18:36:26 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycast.h"

void	update_lights(void)
{
	t_light	*lights;

	lights = ft_lst_to_array(g_data.lights, sizeof(t_light));
	g_data.lights_size = ft_lstsize(g_data.lights);
	if (!lights)
		return ;
	clReleaseMemObject(g_data.lights_buf);
	g_data.lights_buf = mlxcl_create_buffer(g_game->cl_data,
			CL_RD, sizeof(t_light) * ft_max(1, g_data.lights_size), lights);
	free(lights);
	if (g_raycast.raycast_draw_prog)
	{
		mlxcl_set_arg(g_raycast.raycast_draw_prog, 13,
			sizeof(cl_mem), &g_data.lights_buf);
		mlxcl_set_arg(g_raycast.raycast_draw_prog, 14,
			sizeof(int), &g_data.lights_size);
	}
}
