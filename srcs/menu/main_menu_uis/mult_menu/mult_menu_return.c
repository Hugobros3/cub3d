/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_menu_return.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 23:03:24 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:04:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mult_menu.h"

static void	release_return_button(t_game *g, t_ui *ui)
{
	(void)g;
	(void)ui;
	if (g_mult_root->data)
	{
		((void (*)())g_mult_root->data)();
		g_mult_root->data = NULL;
	}
	g_mult_root->active = FALSE;
}

void	init_mult_return_button(void)
{
	t_ui	*ret;
	t_image	*img;

	ret = mlxe_create_ui(g_mult_root, "mult return button");
	img = mlxe_render_text(g_game, g_settings.font,
			"Return", new_color(255, 255, 255, 255));
	ret->size = div2(convert_size(img), v2(15, 15));
	ret->pos = v2(0.01, 0.99 - ret->size.x);
	ret->data_buffer = mlxcl_create_img_buffer(g_game->cl_data, img);
	ret->eval = mlxcl_get_prog(g_game->cl_data, MLXE_EVAL_IMG);
	ret->del = (void (*)(void *ui))free_img_ui;
	ret->on_release = release_return_button;
	free_img(img, g_game->mlx);
}
