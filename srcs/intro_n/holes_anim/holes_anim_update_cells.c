/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   holes_anim_update_cells.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:34:54 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/27 14:23:59 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holes_anim.h"
#include "cub3d.h"

void	holes_anim_update_cells2(t_game *g)
{
	t_list	*curr;
	t_list	*next;
	t_cell	*c;

	curr = g_lst;
	while (curr)
	{
		c = (t_cell *)curr->content;
		if (c->is_hole)
			c->t -= g->d_time * g_hanim.blink_time / 3
				* ft_fmax(1, g_intro.global_intro_speed / 10);
		else
			c->t -= g->d_time * g_hanim.blink_time
				* ft_fmax(1, g_intro.global_intro_speed / 10);
		next = curr->next;
		if (c->t < 0)
		{
			c->t = 0;
			c->blink = FALSE;
			ft_lstremove(&g_lst, curr, NULL);
		}
		curr = next;
	}
}

void	holes_anim_update_cells(t_game *g)
{
	if (!g_lst && g_hanim.done)
	{
		mlxe_remove_loop_hook(g, holes_anim_update_cells);
		mlxe_remove_loop_hook(g, skip_hook);
		free(g_cells);
		load_menu();
	}
	holes_anim_update_cells2(g);
}
