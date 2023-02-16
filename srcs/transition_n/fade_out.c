/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fade_out.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:42:29 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/27 14:25:36 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transition.h"
#include "cub3d.h"

t_bool	fade_out_loop(t_coroutine *c)
{
	(void)c;
	g_transition.fade += g_game->unscaled_d_time / 1.5f;
	if (g_transition.fade >= 1)
	{
		g_transition.fade = 1;
		if (g_transition.halfway)
			g_transition.halfway();
		fade_in_start();
		return (TRUE);
	}
	return (FALSE);
}

void	fade_out_start(void)
{
	mlxe_start_coroutine(g_game, fade_out_loop, NULL, NULL);
}
