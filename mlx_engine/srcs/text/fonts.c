/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:03:49 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/24 16:04:41 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textbuilder.h"

void	mlxe_set_font_quality(void *font, t_iv2 pixel_size)
{
	t_font	*ft;

	ft = (t_font *)font;
	FT_Set_Pixel_Sizes(ft->face, pixel_size.x, pixel_size.y);
}

void	*mlxe_init_font(t_game *g, char *path, t_iv2 quality)
{
	t_font		*font;

	font = ft_malloc(sizeof(t_font));
	font->chars = NULL;
	if (FT_New_Face(g->intern->ft, path, 0, &font->face))
		ft_printf("Unable to load font \'%s\'\n", path);
	font->path = path;
	FT_Set_Pixel_Sizes(font->face, quality.x, quality.y);
	render_font(g, font);
	return (font);
}

void	mlxe_free_font(void *ft)
{
	t_font	*font;

	font = (t_font *)ft;
	ft_lstclear(&font->chars, del_char_info);
	free(font);
}
