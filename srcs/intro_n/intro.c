/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:01:41 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/27 14:24:13 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intro.h"
#include "cub3d.h"

t_cell			*g_cells;
t_intro			g_intro;

void	cell_ui_update(t_ui *ui)
{
	mlxcl_set_arg(ui->eval, 5, sizeof(t_iv2), &g_intro.size);
}

static void	init_ui(void)
{
	t_ui	*ui;
	t_v2	screen_size;
	t_v2	screen_pos;

	screen_pos = v2(0.5f - (g_intro.size.x * g_intro.cell_size / 2),
			0.5f - (g_intro.size.y * g_intro.cell_size / 2));
	screen_size = v2((g_intro.size.x * g_intro.cell_size),
			(g_intro.size.y * g_intro.cell_size));
	ui = mlxe_create_ui(g_intro.bg_ui, "intro cells");
	ui->pos = screen_pos;
	ui->size = screen_size;
	ui->eval = g_intro.eval_cells_basic;
	ui->data = g_cells;
	ui->data_size = sizeof(t_cell) * vlen2i(g_intro.size);
	ui->update = cell_ui_update;
	ui->interactable = FALSE;
	g_intro.ui = ui;
}

static void	init_bg_ui(void)
{
	t_ui	*ui;

	ui = mlxe_create_ui(g_game->ui_root, "intro background");
	ui->pos = v2(0, 0);
	ui->size = v2(1, 1);
	ui->eval = mlxcl_create_ui_program(g_game,
			"./srcs/intro_n/background.cl", "-I./include");
	ui->data = &g_game->time;
	ui->data_size = sizeof(float);
	ui->interactable = FALSE;
	g_intro.bg_ui = ui;
}

static void	init_cell_array(void)
{
	int		i;

	i = 0;
	g_cells = ft_malloc(sizeof(t_cell) * vlen2i(g_intro.size));
	while (i < vlen2i(g_intro.size))
	{
		g_cells[i] = new_cell(iv2(i / g_intro.size.y, i % g_intro.size.y));
		i++;
	}
}

//size + 2 car on rajoute un contour d'EMPTY autour de la carte
void	start_intro(void)
{
	g_intro.eval_cells_basic = mlxcl_register_program(g_game->cl_data,
			EVAL_CELLS_BASIC, "eval_cells_basic", "-I./include");
	g_intro.eval_done_anim = mlxcl_create_ui_program(g_game,
			EVAL_DONE_ANIM, "-I./include");
	g_intro.size = iv2(g_map.size.x + 2, g_map.size.y + 2);
	g_intro.cell_size = ft_fmin(
			PREFERED_CELL_SIZE,
			1.0f / ft_max(g_intro.size.x, g_intro.size.y)
			);
	g_intro.global_intro_speed = INTRO_SPEED;
	mlxe_add_loop_hook(g_game, skip_hook);
	init_cell_array();
	init_bg_ui();
	init_ui();
	verif_animation_start();
}
