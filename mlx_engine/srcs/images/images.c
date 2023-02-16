/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:37:23 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/25 23:28:15 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"
#include <stdlib.h>
#include "images.h"
#include <pthread.h>

#include <stdio.h>

unsigned long	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

t_image	*new_img(void *mlx, t_iv2 size)
{
	t_image	*img;

	img = ft_malloc(sizeof(t_image));
	img->img = mlx_new_image(mlx, size.x, size.y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	img->size = piv2(size.x, size.y);
	return (img);
}

t_image	*dup_img(void *mlx, t_image *img)
{
	t_image	*new;

	new = new_img(mlx, *img->size);
	ft_memcpy(new->addr, img->addr, sizeof(int) * vlen2i(*img->size));
	return (new);
}

t_image	*new_img_file(void *mlx, char *path)
{
	t_image	*img;

	img = ft_malloc(sizeof(t_image));
	img->size = ft_malloc(sizeof(t_iv2));
	img->img = mlx_xpm_file_to_image(mlx, path,
			&(img->size->x), &(img->size->y));
	if (!img->img)
	{
		printf("Bad image.\n");
		exit (3);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (img);
}

t_image	*new_img_fd(void *mlx, int fd)
{
	t_image	*img;

	if (fd < 0)
		return (NULL);
	img = ft_malloc(sizeof(t_image));
	img->size = ft_malloc(sizeof(t_iv2));
	img->img = mlx_xpm_fd_to_image(mlx, fd, &(img->size->x), &(img->size->y));
	if (!img->img)
	{
		printf("Bad image.\n");
		exit (3);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (img);
}
