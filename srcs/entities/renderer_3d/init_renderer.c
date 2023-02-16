/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 23:39:05 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 18:36:22 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_3d.h"
#include "cub3d.h"
#include "raycast.h"

t_renderer_3d	g_renderer_3d;

static void	init_proj_args(void)
{
	t_iv2	proj_scale;

	proj_scale = iv2(PROJ_SIZE, PROJ_SIZE);
	mlxcl_set_arg(g_renderer_3d.proj_prog, 0, sizeof(t_iv2), &proj_scale);
}

static void	init_draw_tris_args(void)
{
	t_iv2	proj_scale;

	proj_scale = iv2(PROJ_SIZE, PROJ_SIZE);
	mlxcl_set_arg(g_renderer_3d.draw_prog, 0, sizeof(t_iv2), &proj_scale);
	mlxcl_set_arg(g_renderer_3d.draw_prog, 3, sizeof(void *),
		&g_renderer_3d.depth_buffer);
	mlxcl_set_arg(g_renderer_3d.draw_prog, 4, sizeof(void *),
		&g_game->frame_buffer);
	mlxcl_set_arg(g_renderer_3d.draw_prog, 5, sizeof(t_iv2), &g_game->size);
	mlxcl_set_arg(g_renderer_3d.draw_prog, 8, sizeof(t_iv2),
		&g_raycast.dists_buffer);
}

static void	init_reset_d_buffer_args(void)
{
	mlxcl_set_arg(g_renderer_3d.reset_d_buffer, 0, sizeof(void *),
		&g_renderer_3d.depth_buffer);
}

void	init_renderer_first(void)
{
	g_renderer_3d.depth_buffer = NULL;
	g_renderer_3d.reset_d_buffer = NULL;
	g_renderer_3d.proj_prog = NULL;
	g_renderer_3d.draw_prog = NULL;
}

void	init_renderer(void)
{
	if (g_renderer_3d.depth_buffer)
		clReleaseMemObject(g_renderer_3d.depth_buffer);
	g_renderer_3d.depth_buffer = mlxcl_create_buffer(g_game->cl_data,
			CL_RW, sizeof(float) * PROJ_SIZE * PROJ_SIZE, NULL);
	g_renderer_3d.reset_d_buffer = mlxcl_register_program(g_game->cl_data,
			RESET_D_BUFFER_FILE, RESET_D_BUFFER_KN, "-I./include");
	g_renderer_3d.proj_prog = mlxcl_register_program(g_game->cl_data,
			PROJECTION_FILE, PROJECTION_KN, "-I./include");
	g_renderer_3d.draw_prog = mlxcl_register_program(g_game->cl_data,
			DRAW_TRIS_FILE, DRAW_TRIS_KN, "-I./include");
	init_reset_d_buffer_args();
	init_proj_args();
	init_draw_tris_args();
}
