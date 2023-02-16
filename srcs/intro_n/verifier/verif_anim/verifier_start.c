/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifier_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 07:21:09 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 01:29:35 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../map_verifier.h"

t_verif_anim	g_vanim;

//lance le processus de vérification de la carte
void	verif_animation_start(void)
{
	g_vanim.verif_anim_time = VERIF_ANIM_BASE_TIME;
	get_cell(iv2(0, g_map.size.y / 2))->infected = 1;
	get_cell(add2i(g_map.spawn_pos, iv2(1, 1)))->spawn = 1;
	mlxe_add_loop_hook(g_game, verif_animation);
}
