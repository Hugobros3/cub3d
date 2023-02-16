/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:48:29 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/20 19:57:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_3d.h"
#include "cub3d.h"
#include "raycast.h"

void	projection(t_entity *e)
{
	t_v4	translation;
	t_v4	rotation;
	t_v4	wp;
	int		local_size;
	int		global_add;

	global_add = 0;
	local_size = 1;
	wp = v4(e->pos.x, e->height, e->pos.y, 0);
	rotation = get_sprite_rot(e);
	translation = v4(0, -1, 25, 0);
	mlxcl_set_arg(g_renderer_3d.proj_prog, 1, sizeof(t_v4), &translation);
	mlxcl_set_arg(g_renderer_3d.proj_prog, 2, sizeof(t_v4), &rotation);
	mlxcl_set_arg(g_renderer_3d.proj_prog, 3, sizeof(void *),
		&e->m->tris_buffer);
	mlxcl_set_arg(g_renderer_3d.proj_prog, 4, sizeof(t_v4), &wp);
	mlxcl_set_arg(g_renderer_3d.proj_prog, 5, sizeof(float), &e->rotation);
	mlxcl_set_arg(g_renderer_3d.proj_prog, 6, sizeof(int),
		&e->m->triangles_count);
	mlxcl_exec_kernel(g_game, g_renderer_3d.proj_prog, local_size,
		e->m->triangles_count + global_add);
}
