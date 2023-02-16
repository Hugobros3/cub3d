/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:55:39 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/25 23:29:03 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "images.h"

#include <stdio.h>

void	free_img(t_image *img, void *mlx)
{
	if (!img)
		return ;
	mlx_destroy_image(mlx, img->img);
	free(img->size);
	free(img);
}

t_color	sample_texture(t_image *img, t_v2 uv)
{
	t_iv2	pos;

	pos.x = (int)(uv.x * img->size->x);
	pos.y = (int)(uv.y * img->size->y);
	return (getpixel(img, pos.x, pos.y));
}

void	fill_image(t_image *img, t_color c)
{
	t_iv2	xy;

	xy = iv2(0, 0);
	while (xy.x < img->size->x)
	{
		xy.y = 0;
		while (xy.y < img->size->y)
		{
			putpixel(img, xy.x, xy.y, c);
			xy.y++;
		}
		xy.x++;
	}
}
