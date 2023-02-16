/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:32:51 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/24 15:41:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGES_H
# define IMAGES_H

# include "libft.h"

typedef struct s_image
{
	void		*img;
	t_iv2		*size;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef t_v4	t_color;

t_color			lerp_color(t_color a, t_color b, float t);
t_color			new_color(int r, int g, int b, int a);
unsigned long	create_rgb(int r, int g, int b);

t_image			*new_img(void *mlx, t_iv2 size);
t_image			*new_img_fd(void *mlx, int fd);
t_image			*dup_img(void *mlx, t_image *img);
t_image			*new_img_file(void *mlx, char *path);
void			free_img(t_image *img, void *mlx);

void			putpixel(t_image *data, int x, int y, t_color color);
t_color			getpixel(t_image *data, int x, int y);
t_color			sample_texture(t_image *img, t_v2 uv);
t_color			alpha_blend(t_color under, t_color over);

void			overlay_image(t_image *dest, t_image *src,
					t_iv2 pos, t_v2 scale);
void			fill_image(t_image *img, t_color c);

#endif
