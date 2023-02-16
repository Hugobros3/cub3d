/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:45:22 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 12:31:02 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycast.h"

void	update_flashlight(void)
{
	if (is_key_down(g_game, KEY_F))
	{
		g_data.flashlight = !g_data.flashlight;
		g_data.flashlight_data->size = FLASHLIGHT_SIZE * g_data.flashlight;
	}
	g_data.flashlight_data->pos = v4(g_player.pos.x,
			g_player.height, g_player.pos.y, 0);
	g_data.flashlight_data->dir = v4(-cos(ft_radians(g_player.rot)),
			-g_player.up_rot / 3, -sin(ft_radians(g_player.rot)), 0);
	update_lights();
}

void	game_loop(t_game *g)
{
	(void)g;
	if (is_key_down(g_game, KEY_ESCAPE))
	{
		switch_escape_menu();
	}
	update_player();
	update_flashlight();
	update_doors();
	raycast();
	draw_entities();
}

void	start_game(void)
{
	mlxe_remove_loop_hook(g_game, menu_background_loop);
	if (g_settings.is_client)
	{
		g_settings.player_height = 0.1f;
		g_settings.vertical_vel = 4.2f;
	}
	mlxe_clear_ui(g_game);
	escape_menu_init();
	minimap_init();
	g_data.flashlight = FALSE;
	g_data.flashlight_data = add_light((t_light){v4(0, 0, 0, 0),
			v4(1, 1, 1, 1), v4(0, 0, 0, 0), 20, 0, TRUE});
	g_player.pos = add2(iv2v2(g_map.spawn_pos), v2(0.5, 0.5));
	g_player.rot = g_map.spawn_rot;
	g_player.height = 0.5f;
	g_player.up_rot = 0;
	g_settings.mouse_lock = TRUE;
	mlxe_add_loop_hook(g_game, game_loop);
}
