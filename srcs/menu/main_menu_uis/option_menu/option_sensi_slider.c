/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_sensi_slider.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 23:02:21 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:05:16 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "option_menu.h"

static t_ui	*init_sensi_label(void)
{
	t_ui	*label;
	t_image	*img;

	label = mlxe_create_ui(g_root, "option sensibility label");
	img = mlxe_render_text(g_game, g_settings.font,
			"Mouse sensi", new_color(255, 255, 255, 255));
	label->interactable = FALSE;
	label->pos = v2(0.01, g_offset);
	label->size = div2(convert_size(img), v2(15, 15));
	label->data_buffer = mlxcl_create_img_buffer(g_game->cl_data, img);
	label->eval = mlxcl_get_prog(g_game->cl_data, MLXE_EVAL_IMG);
	free_img(img, g_game->mlx);
	return (label);
}

static void	sensi_slider_set(float v)
{
	g_settings.mouse_sensi = v * 30;
}

static float	sensi_slider_get(void)
{
	return (g_settings.mouse_sensi / 30);
}

void	init_sensi_slider(void)
{
	t_ui			*label;
	t_slider_info	slider;
	t_ui			*slider_ui;

	label = init_sensi_label();
	slider.border_size = 0.03;
	slider.handle_size = 0.03;
	slider.line_size = 0.02;
	slider.c1 = iv4(255, 255, 255, 255);
	slider.c2 = iv4(180, 180, 180, 255);
	slider.set = sensi_slider_set;
	slider.get = sensi_slider_get;
	slider_ui = create_slider(g_root,
			v2(0.5, label->pos.y + label->size.y / 2 - 0.025), v2(0.45, 0.05),
			slider);
	slider_ui->block_del_on_clear = TRUE;
	((t_ui *)slider_ui->childs->content)->block_del_on_clear = TRUE;
	label->block_del_on_clear = TRUE;
	g_offset += label->size.y;
}
