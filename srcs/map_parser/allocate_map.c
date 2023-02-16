/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:09:09 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:13:58 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "map_parser.h"

char	**skip_to_map(int *offset)
{
	char	**split;
	int		i;

	i = 0;
	split = g_map.str;
	while (split[i] && !ft_isdigit(split[i][0]))
		i++;
	if (offset)
		*offset = i;
	return (split + i);
}

void	allocate_map(void)
{
	int		i;
	char	**split;
	t_iv2	size;

	i = 0;
	size = iv2(0, 0);
	split = skip_to_map(NULL);
	while (split[i])
	{
		size.x = ft_max(size.x, ft_strlen(split[i]));
		i++;
		size.y++;
	}
	g_map.data = ft_malloc(sizeof(int) * size.x * size.y);
	i = 0;
	while (i < size.x * size.y)
	{
		g_map.data[i] = 1;
		i++;
	}
	g_map.size = size;
	ft_printf("Allocated map size: %d %d\n", size.x, size.y);
}
