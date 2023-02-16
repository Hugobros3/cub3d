/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textbuilder.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:01:56 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 00:58:38 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTBUILDER_H
# define TEXTBUILDER_H

# include "mlx_engine_int.h"
# include "mlx_engine.h"

typedef struct s_char_info
{
	char			c;
	t_image			*img;
	t_iv2			size;
	t_iv2			bearing;
	int				advance;
	unsigned char	*buf;
	void			*mlx;
}	t_char_info;

t_char_info	*create_char_info(t_game *g, char c, FT_GlyphSlot glyph);
void		del_char_info(void *content);
int			cmp_char_info(t_char_info *inf1, t_char_info *inf2);
t_char_info	*get_char_info(void *font, char c);

void		mlxe_set_font_quality(void *font, t_iv2 pixel_size);
void		*mlxe_init_font(t_game *g, char *path, t_iv2 quality);
void		mlxe_free_font(void *ft);

void		mlxe_init_ft_lib(t_game *game);

void		render_font(t_game *g, void *font);

#endif