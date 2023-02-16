/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:49:43 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:35:58 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_bool_button(t_ui *ui)
{
	t_boolbutton_info	*infos;

	infos = (t_boolbutton_info *)ui->data;
	if (infos->get)
		infos->v = infos->get();
}

static void	click_bool_button(t_game *g, t_ui *ui)
{
	t_boolbutton_info	*infos;

	(void)g;
	infos = (t_boolbutton_info *)ui->data;
	infos->v = !infos->v;
	if (infos->set)
		infos->set(infos->v);
}

t_ui	*create_bool_button(t_ui *parent, t_v2 pos,
	t_v2 size, t_boolbutton_info infos)
{
	t_ui	*button;	

	button = mlxe_create_ui(parent, "bool button");
	button->interactable = TRUE;
	button->pos = pos;
	button->size = size;
	button->data = ft_memdup(&infos, sizeof(t_boolbutton_info));
	button->data_size = sizeof(t_boolbutton_info);
	button->write_data_each_frame = TRUE;
	button->eval = mlxcl_create_ui_program(g_game,
			"./srcs/ui_elements/bool_button.cl", "");
	button->on_release = click_bool_button;
	button->update = update_bool_button;
	return (button);
}
