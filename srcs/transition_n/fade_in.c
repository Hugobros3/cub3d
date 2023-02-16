/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fade_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:54:53 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/27 14:25:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transition.h"
#include "cub3d.h"

t_bool	fade_in_loop(t_coroutine *c)
{
	(void)c;
	g_transition.fade -= g_game->unscaled_d_time / 1.5f;
	if (g_transition.fade <= 0)
	{
		g_transition.fade = 0;
		if (g_transition.done)
			g_transition.done();
		g_transition.ui->active = FALSE;
		return (TRUE);
	}
	return (FALSE);
}

void	fade_in_start(void)
{
	mlxe_start_coroutine(g_game, fade_in_loop, NULL, NULL);
}
