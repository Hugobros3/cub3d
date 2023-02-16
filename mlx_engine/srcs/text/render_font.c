/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_font.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:05:32 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 21:24:56 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textbuilder.h"

static int	load_char(t_font *ft, char *c)
{
	if (FT_Load_Char(ft->face, *c, FT_LOAD_RENDER))
	{
		ft_printf("	-> Couldn't load '%c' (%d) from font '%s' !\n",
			*c, *c, ft->path);
		(*c)++;
		return (-1);
	}
	return (0);
}

static void	copy_char_inf_to_img(t_game *g, t_char_info *info)
{
	t_image			*out;
	t_iv2			pos;
	unsigned char	n;
	int				a;

	pos = iv2(0, 0);
	out = new_img(g->mlx, info->size);
	while (pos.x < info->size.x)
	{
		while (pos.y < info->size.y)
		{
			n = info->buf[pos.y * (out->size->x) + pos.x];
			a = 1;
			if (n == 0)
				a = 0;
			putpixel(out, pos.x, pos.y, new_color(n, n, n, a));
			pos.y++;
		}
		pos.y = 0;
		pos.x++;
	}
	info->img = out;
}

void	render_font(t_game *g, void *font)
{
	t_char_info		*info;
	t_font			*ft;
	char			c;

	ft = (t_font *)font;
	c = 32;
	while (c < 127)
	{
		if (load_char(ft, &c) < 0)
			continue ;
		info = create_char_info(g, c, ft->face->glyph);
		if (info->size.x == 0 && info->size.y == 0)
		{
			info->img = NULL;
			ft_lstadd_back(&ft->chars, ft_lstnew(info));
			c++;
			continue ;
		}
		copy_char_inf_to_img(g, info);
		ft_lstadd_back(&ft->chars, ft_lstnew(info));
		c++;
	}
}
