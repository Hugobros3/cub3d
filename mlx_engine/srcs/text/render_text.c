/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 20:56:01 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 00:58:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textbuilder.h"

static t_image	*make_text_img(t_game *g,
	char *text, void *font, float *y_max)
{
	t_iv2		size;
	t_iv2		y_minmax;
	int			i;
	t_char_info	*info;

	size = iv2(0, 0);
	i = 0;
	y_minmax = iv2(0, 0);
	while (text[i])
	{
		info = get_char_info(font, text[i++]);
		if (info)
		{
			y_minmax.y = ft_max(y_minmax.y, info->bearing.y);
			y_minmax.x = ft_max(y_minmax.x, info->size.y - info->bearing.y);
			size.x += (info->advance >> 6);
		}
	}
	size.y = y_minmax.y + y_minmax.x;
	*y_max = y_minmax.y;
	if (!size.y && !size.x)
		return (NULL);
	return (new_img(g->mlx, size));
}

typedef struct s_img_cpy_data
{
	t_char_info	*info;
	int			*x_advance;
	int			y_max;
	t_image		*out;
	t_color		col;
}	t_img_cpy_data;

typedef struct s_img_cpy_data2
{
	t_iv2	o;
	t_iv2	pos;
	t_v2	uv;
	t_color	c;
	t_v4	final;
}	t_img_cpy_data2;

static void	cpy_img_data(t_img_cpy_data d)
{
	t_img_cpy_data2	d2;

	if (d.info)
	{
		d2.o = iv2(*d.x_advance, 0);
		d2.o.x += d.info->bearing.x;
		d2.o.y += d.y_max - d.info->bearing.y;
		d2.pos = iv2(d2.o.x, d2.o.y);
		while (d2.pos.x < d2.o.x + d.info->size.x)
		{
			d2.pos.y = d2.o.y;
			while (d2.pos.y < d2.o.y + d.info->size.y)
			{
				d2.uv = ft_invlerp2(iv2v2(d2.o),
						iv2v2(add2i(d2.o, d.info->size)), iv2v2(d2.pos));
				d2.c = sample_texture(d.info->img, d2.uv);
				d2.final = div4(mult4(d2.c, d.col), v4(255, 255, 255, 255));
				d2.final.w = d2.c.x * d.col.w / 255;
				putpixel(d.out, d2.pos.x, d2.pos.y, d2.final);
				d2.pos.y++;
			}
			d2.pos.x++;
		}
		*d.x_advance += (d.info->advance >> 6);
	}
}

t_image	*mlxe_render_text(t_game *g, void *font, char *text, t_color col)
{
	t_img_cpy_data	d;
	t_image			*out;
	float			y_max;
	int				x_advance;
	int				i;

	out = make_text_img(g, text, font, &y_max);
	i = 0;
	x_advance = 0;
	while (text[i])
	{
		d.col = col;
		d.info = get_char_info(font, text[i]);
		d.out = out;
		d.x_advance = &x_advance;
		d.y_max = y_max;
		cpy_img_data(d);
		i++;
	}
	return (out);
}
