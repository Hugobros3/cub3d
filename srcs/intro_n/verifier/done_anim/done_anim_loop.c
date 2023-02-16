/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   done_anim_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 01:26:08 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 01:26:50 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map_verifier.h"
#include "cub3d.h"

int	done_anim_step(void)
{
	if (g_done_anim.d < ft_max(g_intro.size.x, g_intro.size.y) + 4)
	{
		g_done_anim.d += 1.0f * ft_fmax(g_intro.global_intro_speed / 10, 1);
	}
	else
	{
		g_done_anim.c.w -= 3.0f * g_intro.global_intro_speed;
		g_done_anim.c.w = ft_fmax(g_done_anim.c.w, 0);
		if (g_done_anim.c.w <= 0)
			return (1);
	}
	return (0);
}

//boucle de l'animation QUAND FINIT LANCE holes_anim
void	done_animation(t_game *g)
{
	if (done_anim_step())
	{
		g_vanim.done_ui->active = FALSE;
		if (g_map.is_valid == 1)
			holes_anim_start();
		mlxe_remove_loop_hook(g, done_animation);
	}
}
