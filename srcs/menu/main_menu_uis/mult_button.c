/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 03:00:57 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:35:27 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../menu.h"
#include "cub3d.h"

static void	show_main_menu(void)
{
	g_menu.menu_root->active = TRUE;
}

static void	mult_click(t_game *g, t_ui *ui)
{
	(void)g;
	(void)ui;
	g_menu.menu_root->active = FALSE;
	switch_mult_menu(show_main_menu);
}

static void	mult_button_update(t_ui *ui)
{
	(void)ui;
	mlxcl_set_arg(mlxcl_get_prog(g_game->cl_data, "eval_mult_button"),
		5, sizeof(float), &g_game->time);
}

void	mult_button(void)
{
	t_image			*img;
	t_ui			*ui;
	t_mlxcl_prog	*p;

	p = mlxcl_get_prog(g_game->cl_data, "eval_mult_button");
	if (!p)
		p = mlxcl_register_program(g_game->cl_data,
				"./srcs/menu/main_menu_uis/mult_button_eval.cl",
				"eval_mult_button", "");
	mlxcl_set_arg(p, 5, sizeof(float), &g_game->time);
	ui = mlxe_create_ui(g_menu.menu_root, "mult button");
	img = mlxe_render_text(g_game, g_settings.font, "Multiplayer",
			new_color(255, 255, 255, 255));
	ui->pos = v2(0.05, 0.62);
	ui->size = div2(convert_size(img), v2(10, 10));
	ui->data_buffer = mlxcl_create_img_buffer(g_game->cl_data, img);
	ui->eval = p;
	ui->on_release = mult_click;
	ui->update = mult_button_update;
	free_img(img, g_game->mlx);
}
