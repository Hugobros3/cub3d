/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_menu_continue.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 03:05:01 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 15:43:59 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "escape_menu.h"

static void	escape_menu_play_release(t_game *g, t_ui *ui)
{
	(void)g;
	(void)ui;
	switch_escape_menu();
}

void	escape_menu_continue(void)
{
	t_image	*img;
	t_ui	*ui;

	ui = mlxe_create_ui(g_esc_menu.root, "escape menu play");
	img = mlxe_render_text(g_game, g_settings.font,
			"Continue", new_color(255, 255, 255, 255));
	ui->pos = v2(0.01, 0.7);
	ui->size = div2(convert_size(img), v2(10, 10));
	ui->data_buffer = mlxcl_create_img_buffer(g_game->cl_data, img);
	ui->eval = mlxcl_get_prog(g_game->cl_data, MLXE_EVAL_IMG);
	ui->on_release = escape_menu_play_release;
	g_esc_menu.continue_button = ui;
	free_img(img, g_game->mlx);
}