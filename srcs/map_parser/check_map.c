/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:08:12 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:13:22 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "map_parser.h"

void	check_map2(char c, int i, int k, t_bool *spawn_found)
{
	if (c == 'E' || c == 'W'
		|| c == 'S' || c == 'N')
	{
		if (!(*spawn_found))
			*spawn_found = TRUE;
		else
		{
			ft_printf("Error: duplicate spawn '%c' at line '%d'\n",
				c, i + k + 1);
			exit(MAP_ERROR);
		}
	}
	else if (!ft_strchr(MAP_SYMBOLS, c))
	{
		ft_printf("Wrong symbol: %c\n", c);
		exit(MAP_ERROR);
	}
}

void	check_map(void)
{
	int			i;
	int			j;
	int			k;
	t_bool		spawn_found;
	char		**split;

	i = 0;
	spawn_found = FALSE;
	split = skip_to_map(&k);
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			check_map2(split[i][j], i, k, &spawn_found);
			j++;
		}
		i++;
	}
	if (!spawn_found)
	{
		ft_printf("Error: spawn not found !\n");
		exit(MAP_ERROR);
	}
}
