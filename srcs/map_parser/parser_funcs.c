/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:39:14 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:01:23 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"
#include "cub3d.h"

void	parser_check_split(char *smbl, char **split, int n)
{
	if (ft_splitlen(split) != n)
	{
		printf("Error on parsing symbol '%s': bad format\n",
			smbl);
		exit(SYMBOL_ERROR);
	}
}

static void	check_file_access(char *file, char *symbol)
{
	if (access(file, F_OK | R_OK) != 0)
	{
		printf("Error on parsing symbol '%s': file '%s' not found\n",
			symbol, file);
		exit(SYMBOL_ERROR);
	}
}

void	parse_entity(char *symbol, char *str, t_entity **e)
{
	char		**split;
	char		**split2;
	t_v2		pos;
	t_image		*tex;

	split = ft_split(str, ' ');
	parser_check_split(symbol, split, 3);
	split2 = ft_split(split[0], ',');
	parser_check_split(symbol, split2, 2);
	pos = v2(atof(split2[0]), atof(split2[1]));
	ft_freesplit(split2);
	check_file_access(split[1], symbol);
	check_file_access(split[2], symbol);
	ft_lstadd_back(&g_map.files_used, ft_lstnew(ft_strdup(split[1])));
	ft_lstadd_back(&g_map.files_used, ft_lstnew(ft_strdup(split[2])));
	tex = new_img_fd(g_game->mlx, fp_open(split[2], O_RDONLY));
	*e = create_entity(split[1], tex, 1);
	(*e)->pos = pos;
	printf("Parsing symbol %s, pos: (%f,%f), model: %s, texture: %s\n",
		symbol, pos.x, pos.y, split[1], split[2]);
	ft_freesplit(split);
}

void	parse_color(char *symbol, char *file, t_color *c)
{
	char	**rgb;

	rgb = ft_split(file, ',');
	parser_check_split(symbol, rgb, 3);
	c->x = atof(rgb[0]);
	c->y = atof(rgb[1]);
	c->z = atof(rgb[2]);
	c->w = 255;
	printf("Parsing symbol %s, color: %f,%f,%f\n", symbol, c->x, c->y, c->z);
	ft_freesplit(rgb);
	if (!ft_isrange(c->x, 0, 255) || !ft_isrange(c->y, 0, 255)
		|| !ft_isrange(c->z, 0, 255))
	{
		ft_printf("Error on parsing symbol '%s': color not in range [0; 255]\n",
			symbol);
		exit(SYMBOL_ERROR);
	}
}

void	parse_img(char *symbol, char *file, t_image **addr)
{
	ft_printf("Parsing symbol %s, texture: %s\n", symbol, file);
	check_file_access(file, symbol);
	ft_lstadd_back(&g_map.files_used, ft_lstnew(ft_strdup(file)));
	*addr = new_img_file(g_game->mlx, file);
}
