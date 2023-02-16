/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:10:00 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:18:04 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "map_parser.h"

static t_map_tile	spp(t_iv2 p, float r)
{
	g_map.spawn_pos = p;
	g_map.spawn_rot = r;
	return (EMPTY);
}

static void	process_char2(char c, t_iv2 p)
{
	if (c == '|')
	{
		g_map.data[g_map.size.x * p.y + p.x] = -(DOOR + g_map.doors_size);
		g_map.doors_size++;
	}
	else if (c == 'N')
		g_map.data[g_map.size.x * p.y + p.x] = spp(p, 270);
	else if (c == 'S')
		g_map.data[g_map.size.x * p.y + p.x] = spp(p, 90);
	else if (c == 'E')
		g_map.data[g_map.size.x * p.y + p.x] = spp(p, 0);
	else if (c == 'W')
		g_map.data[g_map.size.x * p.y + p.x] = spp(p, 180);
	else if (c == ' ')
		g_map.data[g_map.size.x * p.y + p.x] = EMPTY;
}

void	process_char(char c, t_iv2 p)
{
	if (c == '1')
		g_map.data[g_map.size.x * p.y + p.x] = WALL;
	else if (c == '0')
		g_map.data[g_map.size.x * p.y + p.x] = EMPTY;
	else if (c == 'L')
	{
		map_add_light(v2(p.x + 0.5f, p.y + 0.5f));
		g_map.data[g_map.size.x * p.y + p.x] = EMPTY;
	}
	else if (c == '-')
	{
		g_map.data[g_map.size.x * p.y + p.x] = DOOR + g_map.doors_size;
		g_map.doors_size++;
	}
	else
		process_char2(c, p);
}

void	process_map(void)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	split = g_map.str;
	while (*split && !ft_isdigit((*split)[0]))
		split++;
	while (split[i])
	{
		ft_printf("Processing line '%s'...   ", split[i]);
		j = 0;
		while (split[i][j])
		{
			process_char(split[i][j], iv2(j, i));
			j++;
		}
		i++;
		ft_printf("Done !\n");
	}
}
