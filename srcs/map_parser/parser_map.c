/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:37:34 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:35:36 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "map_parser.h"

static void	init_array_door2(int i)
{
	int	d;

	d = g_map.data[i];
	if (d >= 100)
	{
		g_map.doors[d - 100].pos = v2(i % g_map.size.x + 0.5,
				i / g_map.size.x + 0.5);
		g_map.doors[d - 100].open_amount = 0;
		g_map.doors[d - 100].flipped = FALSE;
	}
	if (d <= -100)
	{
		d = -d;
		g_map.data[i] = d;
		g_map.doors[d - 100].pos = v2(i % g_map.size.x + 0.5,
				i / g_map.size.x + 0.5);
		g_map.doors[d - 100].open_amount = 0;
		g_map.doors[d - 100].flipped = TRUE;
	}
}

static void	init_array_door(void)
{
	int	i;

	i = 0;
	if (g_map.doors_size == 0)
	{
		g_map.doors = NULL;
		return ;
	}
	g_map.doors = malloc(sizeof(t_door) * g_map.doors_size);
	i = 0;
	while (i < vlen2i(g_map.size))
	{
		init_array_door2(i);
		i++;
	}
}

void	print_map(void)
{
	t_iv2	p;

	p = iv2(0, 0);
	while (p.y < g_map.size.y)
	{
		p.x = 0;
		while (p.x < g_map.size.x)
		{
			if (g_map.data[g_map.size.x * p.y + p.x] == 0)
				ft_printf("██");
			else if (g_map.data[g_map.size.x * p.y + p.x] >= DOOR)
			{
				if (g_map.doors[g_map.data[g_map.size.x * p.y + p.x] - 100]
					.flipped)
					ft_printf("| ");
				else
					ft_printf("--");
			}
			else
				ft_printf("░░");
			p.x++;
		}
		ft_printf("\n");
		p.y++;
	}
}

void	parse_map2(void)
{
	check_map();
	allocate_map();
	process_map();
	init_array_door();
	copy_map_lights();
	ft_printf("\nMAP RAW:\n");
	print_map();
}
