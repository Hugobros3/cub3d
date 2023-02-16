/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 23:45:00 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 00:34:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe_ui.h"

void	select_ui(t_game *g, t_ui *ui)
{
	if (g->intern->hovered_ui && g->intern->hovered_ui->clicked)
		return ;
	g->intern->hovered_ui = ui;
	ui->hovered = TRUE;
	if (ui->on_hover)
		ui->on_hover(g, ui);
}

void	unselect_ui(t_game *g)
{
	t_ui	*ui;

	ui = g->intern->hovered_ui;
	if (!ui)
		return ;
	if (ui && ui->clicked)
		return ;
	g->intern->hovered_ui = NULL;
	ui->hovered = FALSE;
	ui->clicked = FALSE;
	if (ui->on_exit)
	{
		printf("%s\n", ui->name);
		ui->on_exit(g, ui);
	}
}
