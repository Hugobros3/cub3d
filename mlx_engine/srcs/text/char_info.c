/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:01:19 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 08:19:27 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textbuilder.h"

void	del_char_info(void *content)
{
	t_char_info	*info;

	info = (t_char_info *)content;
	if (info->img)
		free_img(info->img, info->mlx);
	free(info);
}

int	cmp_char_info(t_char_info *inf1, t_char_info *inf2)
{
	if (inf1->c != inf2->c)
		return (0);
	return (1);
}

t_char_info	*get_char_info(void *font, char c)
{
	t_char_info	*inf;
	t_list		*result;

	inf = ft_malloc(sizeof(t_char_info));
	inf->c = c;
	inf->img = NULL;
	result = ft_lstfind(((t_font *)font)->chars, cmp_char_info, inf);
	del_char_info(inf);
	if (!result)
		return (NULL);
	return ((t_char_info *)result->content);
}

t_char_info	*create_char_info(t_game *g, char c, FT_GlyphSlot glyph)
{
	t_char_info	*info;

	info = ft_malloc(sizeof(t_char_info));
	info->mlx = g->mlx;
	info->c = c;
	info->bearing = iv2(glyph->bitmap_left,
			glyph->bitmap_top);
	info->advance = (int)glyph->advance.x;
	info->buf = glyph->bitmap.buffer;
	info->size = iv2(glyph->bitmap.width,
			glyph->bitmap.rows);
	return (info);
}
