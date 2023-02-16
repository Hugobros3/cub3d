/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:11:57 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/27 14:00:01 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	slider_update(t_ui *slider)
{
	t_slider_info	*infos;
	float			x;
	float			min;
	float			max;

	infos = (t_slider_info *)slider->parent->data;
	min = slider->parent->pos.x + (infos->border_size
			* slider->parent->size.x);
	max = slider->parent->pos.x + slider->parent->size.x
		- (infos->border_size * slider->parent->size.x) - (slider->size.x);
	if (slider->clicked)
	{
		x = (float)mlxe_get_mouse_pos(g_game).x / g_game->size.x
			- slider->size.x / 2;
		slider->pos.x = ft_clampf(min, max, x);
		if (infos->set)
			infos->set(ft_invlerp(min, max, slider->pos.x));
	}
	else
	{
		if (infos->get)
			slider->pos.x = ft_lerp(min, max, ft_clampf(0, 1, infos->get()));
	}
}

t_ui	*create_slider(t_ui *parent, t_v2 pos, t_v2 size, t_slider_info infos)
{
	t_ui	*slider_bg;
	t_ui	*slider_handle;
	t_v2	handle_size;

	slider_bg = mlxe_create_ui(parent, "slider_bg");
	slider_bg->interactable = TRUE;
	slider_bg->pos = pos;
	slider_bg->size = size;
	slider_bg->data = ft_memdup(&infos, sizeof(t_slider_info));
	slider_bg->data_size = sizeof(t_slider_info);
	slider_bg->write_data_each_frame = FALSE;
	slider_bg->eval = mlxcl_create_ui_program(g_game,
			"./srcs/ui_elements/slider_bg.cl", "");
	handle_size = v2(0.02, size.y);
	slider_handle = mlxe_create_ui(slider_bg, "slider_handle");
	slider_handle->active = TRUE;
	slider_handle->interactable = TRUE;
	slider_handle->pos = add2(pos, v2(size.x / 2
				- handle_size.x / 2, 0));
	slider_handle->size = handle_size;
	slider_handle->eval = mlxcl_create_ui_program(g_game,
			"./srcs/ui_elements/slider_handle.cl", "");
	slider_handle->update = slider_update;
	return (slider_bg);
}
