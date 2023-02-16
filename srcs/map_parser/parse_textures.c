/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:00:03 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 15:58:36 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"
#include "cub3d.h"

static t_image	*default_texture(void)
{
	t_image	*img;

	img = new_img(g_game->mlx, iv2(1, 1));
	putpixel(img, 0, 0, new_color(COLOR_WHITE));
	putpixel(img, 1, 0, new_color(COLOR_WHITE));
	putpixel(img, 0, 1, new_color(COLOR_WHITE));
	putpixel(img, 1, 1, new_color(COLOR_WHITE));
	return (img);
}

void	parse_textures(void)
{
	parse_smbl_required("NO", (t_v) &(g_map.no), (t_f)parse_img);
	parse_smbl_required("SO", (t_v) &(g_map.so), (t_f)parse_img);
	parse_smbl_required("EA", (t_v) &(g_map.ea), (t_f)parse_img);
	parse_smbl_required("WE", (t_v) &(g_map.we), (t_f)parse_img);
	parse_smbl_required("D", (t_v) &(g_map.door), (t_f)parse_img);
	if (!parse_smbl_optional("F", (t_v) & g_map.floor_col, (t_f)parse_color))
		g_map.floor_col = new_color(COLOR_WHITE);
	if (!parse_smbl_optional("C", (t_v) & g_map.ceil_col, (t_f)parse_color))
		g_map.ceil_col = new_color(COLOR_WHITE);
	if (!parse_smbl_optional("FT", (t_v) &(g_map.floor), (t_f)parse_img))
		g_map.floor = default_texture();
	if (!parse_smbl_optional("CT", (t_v) &(g_map.ceil), (t_f)parse_img))
		g_map.ceil = default_texture();
}
