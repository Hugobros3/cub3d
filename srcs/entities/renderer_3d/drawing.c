/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:53:09 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/16 16:28:48 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_3d.h"
#include "cub3d.h"
#include "raycast.h"

void	drawing(t_entity *e, t_iv2 start, t_iv2 end)
{
	float	d;

	d = ft_dist2(e->pos, g_player.pos);
	mlxcl_set_arg(g_renderer_3d.draw_prog, 1, sizeof(void *),
		&e->m->tris_buffer);
	mlxcl_set_arg(g_renderer_3d.draw_prog, 2, sizeof(void *), &e->tex_buf);
	mlxcl_set_arg(g_renderer_3d.draw_prog, 6, sizeof(t_iv2), &start);
	mlxcl_set_arg(g_renderer_3d.draw_prog, 7, sizeof(t_iv2), &end);
	mlxcl_set_arg(g_renderer_3d.draw_prog, 9, sizeof(float), &d);
	mlxcl_set_arg(g_renderer_3d.draw_prog, 10, sizeof(void *),
		&g_data.lights_buf);
	mlxcl_set_arg(g_renderer_3d.draw_prog, 11, sizeof(int),
		&g_data.lights_size);
	mlxcl_exec_kernel(g_game, g_renderer_3d.draw_prog, 1,
		e->m->triangles_count);
}
