/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   done_anim_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 22:43:01 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/03 16:18:31 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map_verifier.h"
#include "cub3d.h"

t_done_anim	g_done_anim;

static void	done_anim_init_ui(void)
{
	t_ui	*ui;

	ui = mlxe_create_ui(g_intro.ui, "done anim ui");
	ui->pos = g_intro.ui->pos;
	ui->size = g_intro.ui->size;
	ui->eval = g_intro.eval_done_anim;
	ui->data = &g_done_anim;
	ui->data_size = sizeof(t_done_anim);
	ui->write_data_each_frame = TRUE;
	ui->interactable = FALSE;
	g_vanim.done_ui = ui;
}

void	start_done_anim(t_iv2 last_infect)
{
	if (g_map.is_valid)
	{
		g_done_anim.p = v2(last_infect.x + 0.5f, last_infect.y + 0.5f);
		g_done_anim.c = new_color(COLOR_GOOD1);
	}
	else
	{
		g_done_anim.p = v2(g_map.spawn_pos.x + 0.5f, g_map.spawn_pos.y + 0.5f);
		g_done_anim.c = new_color(COLOR_WRONG);
	}
	g_done_anim.d = 0;
	g_done_anim.size = g_intro.size;
	done_anim_init_ui();
	mlxe_add_loop_hook(g_game, done_animation);
}
