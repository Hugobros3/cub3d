/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_button.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 03:00:57 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:05:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../menu.h"
#include "cub3d.h"

static void	options_return(void)
{
	g_menu.menu_root->active = TRUE;
}

static void	options_click(t_game *g, t_ui *ui)
{
	(void)g;
	(void)ui;
	g_menu.menu_root->active = FALSE;
	switch_option_menu(options_return);
}

void	options_button(void)
{
	t_image	*img;
	t_ui	*ui;

	ui = mlxe_create_ui(g_menu.menu_root, "options button");
	img = mlxe_render_text(g_game, g_settings.font, "Options",
			new_color(255, 255, 255, 255));
	ui->pos = v2(0.05, 0.78);
	ui->size = div2(convert_size(img), v2(10, 10));
	ui->data_buffer = mlxcl_create_img_buffer(g_game->cl_data, img);
	ui->eval = mlxcl_get_prog(g_game->cl_data, MLXE_EVAL_IMG);
	ui->on_click = options_click;
	free_img(img, g_game->mlx);
}
