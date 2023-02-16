/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_algo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 09:15:37 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 01:28:12 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map_verifier.h"
#include "cub3d.h"

//check is la tile a position p est valide pour etre infécté
int	is_tile_valid(t_iv2 p)
{
	int	is_wall;
	int	neighborg_wall;

	neighborg_wall = 0;
	is_wall = g_map.data[g_map.size.x * p.y + p.x] == WALL;
	if (g_map.data[g_map.size.x * (p.y + 1) + p.x] == WALL)
		neighborg_wall = 1;
	if (g_map.data[g_map.size.x * (p.y - 1) + p.x] == WALL)
		neighborg_wall = 1;
	if (g_map.data[g_map.size.x * p.y + p.x + 1] == WALL)
		neighborg_wall = 1;
	if (g_map.data[g_map.size.x * p.y + p.x - 1] == WALL)
		neighborg_wall = 1;
	return (!is_wall && neighborg_wall);
}

//infecte toute les cellules qui sont a infécté
void	process_cells(void)
{
	t_iv2	p;

	p = iv2(0, 0);
	while (p.x < g_intro.size.x)
	{
		p.y = 0;
		while (p.y < g_intro.size.y)
		{
			if (get_cell(p)->to_infect)
			{
				get_cell(p)->infected = 1;
				get_cell(p)->to_infect = 0;
				g_vanim.last_cell_infec = p;
			}
			p.y++;
		}
		p.x++;
	}
}

/*
infecte toute les cellules autour de la cellule a position p
renvoie un boolean qui informe de si on a infécté une cellule ou non
*/

static int	cell_infect2(t_iv2 p, int infected_cell)
{
	t_cell	*c;
	t_iv2	p2;

	p2 = add2i(p, iv2(0, 1));
	c = get_cell(p2);
	if (c && !c->infected && check_wall(p2))
	{
		c->to_infect = 1;
		infected_cell = 1;
	}
	p2 = add2i(p, iv2(0, -1));
	c = get_cell(p2);
	if (c && !c->infected && check_wall(p2))
	{
		c->to_infect = 1;
		infected_cell = 1;
	}
	return (infected_cell);
}

int	cell_infect(t_iv2 p)
{
	t_cell	*c;
	t_iv2	p2;
	int		infected_cell;

	infected_cell = 0;
	p2 = add2i(p, iv2(1, 0));
	c = get_cell(add2i(p, iv2(1, 0)));
	if (c && !c->infected && check_wall(p2))
	{
		c->to_infect = 1;
		infected_cell = 1;
	}
	p2 = add2i(p, iv2(-1, 0));
	c = get_cell(p2);
	if (c && !c->infected && check_wall(p2))
	{
		c->to_infect = 1;
		infected_cell = 1;
	}
	return (cell_infect2(p, infected_cell));
}

/*
infecte les cellules a infecter
si aucune cellules infécté ce tour la -> on est bon
si la cellule spawn est infécté -> on est pas bon
return 1/-1 quand finit, 0 quand pas finit
*/
int	verif_algo(void)
{
	t_iv2	p;
	int		cell_infected;

	cell_infected = 0;
	process_cells();
	p = iv2(0, 0);
	while (p.x < g_intro.size.x)
	{
		p.y = 0;
		while (p.y < g_intro.size.y)
		{
			if (get_cell(p)->infected)
				cell_infected += cell_infect(p);
			p.y++;
		}
		p.x++;
	}
	if (get_cell(g_map.spawn_pos)->infected)
		return (-1);
	if (!cell_infected)
		return (1);
	return (0);
}
