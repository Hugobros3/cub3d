/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:13:24 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:31:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "cub3d.h"

t_menu	g_menu;

void	lock_buttons(void)
{
	g_menu.menu_root->interactable = FALSE;
}

static void	menu_root_init(void)
{
	t_ui	*ui;

	ui = mlxe_create_ui(g_game->ui_root, "menu root");
	ui->pos = v2(0.033, 0.68);
	ui->size = v2(0.175, 0.275);
	ui->eval = mlxcl_create_ui_program(g_game,
			"./srcs/menu/menu_root.cl", "-I./include");
	ui->data = NULL;
	ui->data_size = 0;
	g_menu.menu_root = ui;
}

void	load_menu_clear_ui(void)
{
	g_settings.mouse_lock = FALSE;
	mlxe_remove_loop_hook(g_game, game_loop);
	if (g_data.flashlight_data)
		remove_light(g_data.flashlight_data);
	g_player.height = 0.5f;
	g_player.up_rot = 0;
	raycast_init();
	init_renderer();
	mlxe_clear_ui(g_game);
	menu_root_init();
	start_button();
	options_button();
	quit_button();
	mult_button();
	find_place();
	init_mult_menu();
	mlxe_add_loop_hook(g_game, menu_background_loop);
}

void	load_menu(void)
{
	make_transition(NULL, load_menu_clear_ui, NULL);
}
