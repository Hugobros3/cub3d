/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:58:51 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/25 23:48:02 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe_ui.h"

static void	mlxe_create_ui2(t_ui *ui)
{
	ui->on_click = NULL;
	ui->on_hover = NULL;
	ui->on_release = NULL;
	ui->on_exit = NULL;
	ui->clicked = FALSE;
	ui->hovered = FALSE;
	ui->update = NULL;
	ui->eval = NULL;
	ui->data = NULL;
	ui->data_size = 0;
	ui->data_buffer = NULL;
	ui->write_data_each_frame = TRUE;
}

t_ui	*mlxe_create_ui(t_ui *parent, char *name)
{
	t_ui	*out;

	out = ft_malloc(sizeof(t_ui));
	out->parent = parent;
	out->childs = NULL;
	if (parent)
		ft_lstadd_back(&parent->childs, ft_lstnew(out));
	mlxe_create_ui2(out);
	out->del = NULL;
	out->pos = v2(0, 0);
	out->size = v2(0, 0);
	out->rot = 0;
	out->active = TRUE;
	out->interactable = TRUE;
	out->block_del_on_clear = FALSE;
	out->name = ft_strdup(name);
	mlxe_log(CYN"Created"RESET" ui '%s' at address "YEL"%p"RESET"\n", name, out);
	return (out);
}
