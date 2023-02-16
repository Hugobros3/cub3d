/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifier_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 09:05:51 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/27 14:24:27 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map_verifier.h"
#include "cub3d.h"

//on ne fait s'executer la boucle que tout les UPDATE_TIME secondes
#ifdef OSX

int	verif_update_timer(void)
{
	static float	timer = 0;

	if (timer < g_vanim.verif_anim_time / g_intro.global_intro_speed)
	{
		timer += g_game->d_time;
		return (0);
	}
	else
		timer = 0;
	return (1);
}
#else

int	verif_update_timer(void)
{
	static float	timer = 0;

	if (timer < g_vanim.verif_anim_time / g_intro.global_intro_speed)
	{
		timer += g_game->d_time;
		return (0);
	}
	else
		timer = 0;
	return (1);
}
#endif

//boucle de l'animation QUAND FINIT LANCE verif_done_animation
void	verif_animation(t_game *g)
{
	int	k;

	(void)g;
	if (!verif_update_timer())
		return ;
	k = verif_algo();
	if (k != 0)
	{
		if (k == -1)
		{
			g_map.is_valid = FALSE;
			ft_printf("Invalid map !");
		}
		else
		{
			g_map.is_valid = TRUE;
			ft_printf("Done !\n");
		}
		mlxe_remove_loop_hook(g_game, verif_animation);
		start_done_anim(g_vanim.last_cell_infec);
	}
}
