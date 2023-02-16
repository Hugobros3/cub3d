/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:57:26 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 01:34:19 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transition.h"

t_transition	g_transition;

void	init_transition(void)
{
	t_ui	*ui;

	ui = mlxe_create_ui(g_game->ui_root, "transition");
	ui->pos = v2(0, 0);
	ui->size = v2(1, 1);
	ui->data = &g_transition.fade;
	ui->data_size = sizeof(float);
	ui->eval = mlxcl_create_ui_program(g_game, EVAL_FADE, "-I./include");
	ui->write_data_each_frame = TRUE;
	ui->active = FALSE;
	ui->block_del_on_clear = TRUE;
	g_transition.ui = ui;
}

void	make_transition(void (*start)(), void (*halfway)(), void (*done)())
{
	g_transition.halfway = halfway;
	g_transition.done = done;
	g_transition.ui->active = TRUE;
	g_transition.fade = 0;
	if (start)
		start();
	fade_out_start();
}
