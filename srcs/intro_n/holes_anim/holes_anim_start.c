/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   holes_anim_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 03:39:10 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/16 16:57:31 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holes_anim.h"
#include "cub3d.h"

t_list	*g_lst;
t_hanim	g_hanim;

void	holes_anim_start(void)
{
	g_hanim.update_time = .05f;
	g_hanim.blink_time = 1.5f;
	g_hanim.done = FALSE;
	g_lst = NULL;
	mlxe_add_loop_hook(g_game, holes_anim_loop);
	mlxe_add_loop_hook(g_game, holes_anim_update_cells);
}
