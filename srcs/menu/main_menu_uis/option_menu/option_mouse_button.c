/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_mouse_button.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:46:16 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:05:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "option_menu.h"

static t_ui	*init_mouse_label(void)
{
	t_ui	*label;
	t_image	*img;

	label = mlxe_create_ui(g_root, "option mouse label");
	img = mlxe_render_text(g_game, g_settings.font,
			"Mouse control", new_color(255, 255, 255, 255));
	label->interactable = FALSE;
	label->pos = v2(0.01, g_offset);
	label->size = div2(convert_size(img), v2(15, 15));
	label->data_buffer = mlxcl_create_img_buffer(g_game->cl_data, img);
	label->eval = mlxcl_get_prog(g_game->cl_data, MLXE_EVAL_IMG);
	free_img(img, g_game->mlx);
	return (label);
}

static void	mouse_control_set(t_bool b)
{
	g_settings.mouse_controls = b;
}

static t_bool	mouse_control_get(void)
{
	return (g_settings.mouse_controls);
}

void	init_mouse_control_button(void)
{
	t_ui				*label;
	t_boolbutton_info	infos;

	label = init_mouse_label();
	infos.c1 = iv4(255, 255, 255, 255);
	infos.c2 = iv4(90, 90, 90, 255);
	infos.get = mouse_control_get;
	infos.set = mouse_control_set;
	infos.v = g_settings.mouse_controls;
	create_bool_button(g_root,
		v2(0.5, label->pos.y + label->size.y / 2 - 0.025),
		v2(label->size.y, label->size.y),
		infos);
}
