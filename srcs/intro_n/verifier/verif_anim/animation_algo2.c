/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_algo2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 22:37:32 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 01:28:44 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map_verifier.h"
#include "cub3d.h"

//vu qu'on rajoute un conteur de EMPTY, on dois
//gérer le cas ou on est sur ce contour
int	check_wall(t_iv2 p)
{
	if (p.x == 0 || p.y == 0 || p.x == g_map.size.x + 1
		|| p.y == g_map.size.y + 1)
		return (EMPTY);
	else
		return (g_map.data[g_map.size.x * (p.y - 1) + (p.x - 1)]);
}
