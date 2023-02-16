/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:50:11 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 18:36:44 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "cub3d.h"

static void	raycast_init_kn_args(void)
{
	t_mlxcl_prog	*p;

	p = g_raycast.raycast_prog;
	mlxcl_set_arg(p, 0, sizeof(cl_mem), &g_raycast.dists_buffer);
	mlxcl_set_arg(p, 1, sizeof(cl_mem), &g_raycast.ray_data_buffer);
	mlxcl_set_arg(p, 2, sizeof(cl_mem), &g_raycast.map_buffer);
	mlxcl_set_arg(p, 3, sizeof(t_iv2), &g_map.size);
	mlxcl_set_arg(p, 5, sizeof(cl_mem), &g_raycast.doors_buffer);
}

static void	raycast_draw_init_kn_args(void)
{
	t_mlxcl_prog	*p;

	p = g_raycast.raycast_draw_prog;
	mlxcl_set_arg(p, 0, sizeof(cl_mem), &g_raycast.dists_buffer);
	mlxcl_set_arg(p, 1, sizeof(cl_mem), &g_raycast.ray_data_buffer);
	mlxcl_set_arg(p, 2, sizeof(cl_mem), &g_game->frame_buffer);
	mlxcl_set_arg(p, 3, sizeof(cl_mem), &g_raycast_textures.no);
	mlxcl_set_arg(p, 4, sizeof(cl_mem), &g_raycast_textures.so);
	mlxcl_set_arg(p, 5, sizeof(cl_mem), &g_raycast_textures.ea);
	mlxcl_set_arg(p, 6, sizeof(cl_mem), &g_raycast_textures.we);
	mlxcl_set_arg(p, 7, sizeof(cl_mem), &g_raycast_textures.floor);
	mlxcl_set_arg(p, 8, sizeof(cl_mem), &g_raycast_textures.ceil);
	mlxcl_set_arg(p, 9, sizeof(t_v4), &g_map.floor_col);
	mlxcl_set_arg(p, 10, sizeof(t_v4), &g_map.ceil_col);
	mlxcl_set_arg(p, 11, sizeof(cl_mem), &g_raycast_textures.door);
	mlxcl_set_arg(p, 13, sizeof(cl_mem), &g_data.lights_buf);
	mlxcl_set_arg(p, 14, sizeof(int), &g_data.lights_size);
	mlxcl_set_arg(p, 15, sizeof(cl_mem), &g_raycast.map_buffer);
	mlxcl_set_arg(p, 16, sizeof(t_iv2), &g_map.size);
	mlxcl_set_arg(p, 16, sizeof(t_iv2), &g_map.size);
	mlxcl_set_arg(p, 18, sizeof(t_iv2), &g_raycast.doors_buffer);
}

static void	textures_init(void)
{
	g_raycast_textures.no = mlxcl_create_img_buffer(g_game->cl_data, g_map.no);
	g_raycast_textures.so = mlxcl_create_img_buffer(g_game->cl_data, g_map.so);
	g_raycast_textures.ea = mlxcl_create_img_buffer(g_game->cl_data, g_map.ea);
	g_raycast_textures.we = mlxcl_create_img_buffer(g_game->cl_data, g_map.we);
	g_raycast_textures.door = mlxcl_create_img_buffer(g_game->cl_data,
			g_map.door);
	g_raycast_textures.floor = mlxcl_create_img_buffer(g_game->cl_data,
			g_map.floor);
	g_raycast_textures.ceil = mlxcl_create_img_buffer(g_game->cl_data,
			g_map.ceil);
}

static void	raycast_init2(void)
{
	if (g_raycast.map_buffer)
		clReleaseMemObject(g_raycast.map_buffer);
	if (g_raycast.dists_buffer)
		clReleaseMemObject(g_raycast.dists_buffer);
	if (g_raycast.ray_data_buffer)
		clReleaseMemObject(g_raycast.ray_data_buffer);
	if (g_raycast.doors_buffer)
		clReleaseMemObject(g_raycast.doors_buffer);
	g_raycast.map_buffer = mlxcl_create_buffer(g_game->cl_data, CL_RD,
			sizeof(int) * vlen2i(g_map.size), g_map.data);
	g_raycast.dists_buffer = mlxcl_create_buffer(g_game->cl_data, CL_RW,
			sizeof(float) * g_game->size.x, NULL);
	g_raycast.ray_data_buffer = mlxcl_create_buffer(g_game->cl_data, CL_RW,
			sizeof(t_ray_data) * g_game->size.x, NULL);
	g_raycast.doors_buffer = mlxcl_create_buffer(g_game->cl_data, CL_RD,
			sizeof(t_door) * ft_max(g_map.doors_size, 1), g_map.doors);
}

void	raycast_init(void)
{
	static t_bool	progs_init = FALSE;
	static t_bool	map_m_init = FALSE;

	if (!progs_init)
	{
		progs_init = TRUE;
		g_raycast.raycast_prog = mlxcl_register_program(g_game->cl_data,
				RAYCAST_KN, RAYCAST_KN_NAME, "-I./include");
		g_raycast.raycast_draw_prog = mlxcl_register_program(g_game->cl_data,
				RAYCAST_DRAW_KN, RAYCAST_DRAW_KN_NAME, "-I./include");
	}
	raycast_init2();
	if (!map_m_init)
	{
		pthread_mutex_init(&g_raycast.map_buffer_m, NULL);
		map_m_init = TRUE;
	}
	textures_init();
	raycast_init_kn_args();
	raycast_draw_init_kn_args();
}
