/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cells.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:33:16 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 01:24:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intro.h"
#include "cub3d.h"

t_cell	*get_cell(t_iv2 pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= g_intro.size.x
		|| pos.y >= g_intro.size.y)
		return (NULL);
	return (&(g_cells[pos.x * g_intro.size.y + pos.y]));
}

t_cell	new_cell(t_iv2 pos)
{
	t_cell	cell;

	if (pos.x == 0 || pos.y == 0 || pos.x == g_map.size.x + 1
		|| pos.y == g_map.size.y + 1)
		cell.tile = EMPTY;
	else
		cell.tile = g_map.data[g_map.size.x * (pos.y - 1) + (pos.x - 1)];
	cell.infected = 0;
	cell.to_infect = 0;
	cell.spawn = 0;
	cell.blink = 0;
	cell.flag = 0;
	cell.is_hole = 0;
	cell.t = 0;
	return (cell);
}
