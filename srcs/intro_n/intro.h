/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:47:54 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 15:32:04 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTRO_H
# define INTRO_H

# include "libft.h"
# include "cells_defines.h"
# include "mlx_engine.h"

# define HOLE_LINE_COUNT 4
# define HOLE_INNER_CIRCLE 2

# define EVAL_CELLS_BASIC "srcs/intro_n/eval_cell_basic.cl"
# define EVAL_DONE_ANIM "srcs/intro_n/verifier/done_anim/done_anim.cl"

# ifdef LINUX
#  define INTRO_SPEED_UP 20
#  define INTRO_SPEED 1
# else
#  define INTRO_SPEED_UP 60
#  define INTRO_SPEED 3
# endif

//flag et timer sont utilisé pour les différentes animations
typedef struct s_cell
{
	int		tile;
	t_bool	infected;
	t_bool	to_infect;
	t_bool	spawn;
	t_bool	blink;
	t_bool	flag;
	t_bool	is_hole;
	float	t;
}	t_cell;

typedef struct s_intro
{
	t_ui			*ui;
	t_ui			*bg_ui;
	t_iv2			size;
	float			cell_size;

	t_mlxcl_prog	*eval_cells_basic;
	t_mlxcl_prog	*eval_done_anim;

	float			global_intro_speed;
	t_ui			*prompt;
}	t_intro;

t_cell	new_cell(t_iv2 pos);
t_cell	*get_cell(t_iv2 pos);

void	verif_animation_start(void);
void	holes_anim_start(void);

void	skip_hook(t_game *g);

extern t_cell	*g_cells;
extern t_intro	g_intro;

#endif