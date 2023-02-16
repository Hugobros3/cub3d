/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:09:44 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:00:36 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	*copy_hole_data(void *d)
{
	return (ft_memdup(d, sizeof(t_v2)));
}

static void	*copy_light_data(void *d)
{
	return (ft_memdup(d, sizeof(t_light)));
}

static void	duplicate_map2(t_map *new_map, t_map *m)
{
	printf("Duplicating image NO\n");
	new_map->no = dup_img(g_game->mlx, m->no);
	printf("Duplicating image SO\n");
	new_map->so = dup_img(g_game->mlx, m->so);
	printf("Duplicating image WE\n");
	new_map->we = dup_img(g_game->mlx, m->we);
	printf("Duplicating image EA\n");
	new_map->ea = dup_img(g_game->mlx, m->ea);
	printf("Duplicating image DOOR\n");
	new_map->door = dup_img(g_game->mlx, m->door);
	printf("Duplicating image CEIL\n");
	new_map->ceil = dup_img(g_game->mlx, m->ceil);
	printf("Duplicating image FLOOR\n");
	new_map->floor = dup_img(g_game->mlx, m->floor);
}

t_map	*duplicate_map(t_map *m)
{
	t_map	*new_map;

	printf("Duplicating map...\n");
	new_map = ft_malloc(sizeof(t_map));
	ft_bzero(new_map, sizeof(t_map));
	duplicate_map2(new_map, m);
	new_map->ceil_col = m->ceil_col;
	new_map->floor_col = m->floor_col;
	new_map->str = ft_dupsplit(m->str);
	new_map->size = m->size;
	new_map->data = ft_memdup(m->data, sizeof(int) * vlen2i(m->size));
	new_map->holes = ft_lstmap(m->holes, copy_hole_data, free);
	new_map->is_valid = m->is_valid;
	new_map->spawn_pos = m->spawn_pos;
	new_map->spawn_rot = m->spawn_rot;
	new_map->doors = ft_memdup(m->doors, sizeof(t_door) * m->doors_size);
	new_map->doors_size = m->doors_size;
	new_map->lights = ft_lstmap(m->lights, copy_light_data, free);
	new_map->lights_size = m->lights_size;
	new_map->files_used = ft_lstmap(m->files_used,
			(void *(*)(void *))ft_strdup, free);
	printf("-> Done\n");
	return (new_map);
}
