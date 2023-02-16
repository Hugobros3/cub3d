/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 06:45:20 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 15:11:37 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycast.h"

static void	init_gmap(void)
{
	g_map.holes = NULL;
	g_map.is_valid = 0;
	g_map.doors_size = 0;
	g_map.lights = NULL;
	g_map.lights_size = 0;
	g_map.files_used = NULL;
}

static void	init_gsettings(void)
{
	g_settings.font = mlxe_init_font(g_game, MAIN_FONT, iv2(1024, 1024));
	g_settings.holes_count = HOLES_COUNT;
	g_settings.ingame_initialized = FALSE;
	g_settings.player_height = 0.5f;
	g_settings.vertical_vel = 3.0f;
	g_settings.is_client = FALSE;
	g_settings.is_server = FALSE;
	g_settings.mouse_sensi = 20;
	g_settings.mouse_lock = FALSE;
	g_settings.mouse_controls = FALSE;
}

static void	init_graycast(void)
{
	g_raycast.raycast_draw_prog = NULL;
	g_raycast.raycast_prog = NULL;
	g_raycast.dists_buffer = NULL;
	g_raycast.doors_buffer = NULL;
	g_raycast.map_buffer = NULL;
	g_raycast.ray_data_buffer = NULL;
}

void	init(void)
{
	t_light	l;

	g_files_pool = NULL;
	init_gmap();
	init_gsettings();
	init_graycast();
	g_data.entities = NULL;
	g_data.multiplayer_entities = NULL;
	g_data.flashlight = TRUE;
	g_data.map_save = NULL;
	g_data.player_count = 0;
	l = (t_light){.size = 0};
	g_data.lights = NULL;
	g_data.lights_buf = mlxcl_create_buffer(g_game->cl_data,
			CL_RD, sizeof(t_light), &l);
	get_user_name();
	g_player.fov = 60;
	g_player.up_rot = 0;
	g_player.height = g_settings.player_height;
	mlxe_add_loop_hook(g_game, stop_multi_loop);
	init_renderer_first();
	init_transition();
	init_multiplayer();
	init_option_menu();
}
