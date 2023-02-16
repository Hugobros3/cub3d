/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:34:03 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/23 20:03:38 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cleanup.h"

void	cleanup_map(t_map *map)
{
	free(map->data);
	free(map->doors);
	free_img(map->no, g_game->mlx);
	free_img(map->so, g_game->mlx);
	free_img(map->ea, g_game->mlx);
	free_img(map->we, g_game->mlx);
	free_img(map->floor, g_game->mlx);
	free_img(map->ceil, g_game->mlx);
	free_img(map->door, g_game->mlx);
	ft_lstclear(&map->files_used, free);
	ft_lstclear(&map->lights, free);
	ft_lstclear(&map->holes, free);
	ft_freesplit(map->str);
}
