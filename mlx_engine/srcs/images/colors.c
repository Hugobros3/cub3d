/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 23:27:00 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/25 23:27:41 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "images.h"
#include "mlx_engine_int.h"
#include "mlx_engine.h"

t_color	alpha_blend(t_color under, t_color over)
{
	float	over_a;
	float	under_a;
	t_color	out;

	over_a = ft_invlerp(0, 255, over.w);
	under_a = ft_invlerp(0, 255, under.w);
	out = new_color(
			over_a * over.x + (1 - over_a) * under.x * under_a,
			over_a * over.y + (1 - over_a) * under.y * under_a,
			over_a * over.z + (1 - over_a) * under.z * under_a,
			(over_a + under_a * (1 - over_a)) * 255
			);
	return (out);
}

t_color	lerp_color(t_color a, t_color b, float t)
{
	t_color	out;

	if (t < 0)
		t = 0;
	if (t > 1)
		t = 1;
	out = (t_color){
		.x = a.x + (b.x - a.x) * t,
		.y = a.y + (b.y - a.y) * t,
		.z = a.z + (b.z - a.z) * t,
		.w = a.w + (b.w - a.w) * t};
	return (out);
}

t_color	new_color(int r, int g, int b, int a)
{
	return ((t_color){.x = r, .y = g, .z = b, .w = a});
}

void	putpixel(t_image *data, int x, int y, t_color col)
{
	char	*dst;
	int		hex;
	t_iv4	c_int;

	if (x >= data->size->x || y >= data->size->y || x < 0 || y < 0)
		return ;
	c_int = v4iv4(col);
	hex = ((((c_int.w) & 0xff) << 24) + ((c_int.x & 0xff) << 16)
			+ ((c_int.y & 0xff) << 8) + (c_int.z & 0xff));
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = hex;
}

t_color	getpixel(t_image *data, int x, int y)
{
	int				pixel;
	t_color			rgb;
	char			*loc;

	x = ft_clamp(0, data->size->x, x);
	y = ft_clamp(0, data->size->y, y);
	loc = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	pixel = *(unsigned int *)loc;
	rgb.w = ((pixel >> 24) & 0xFF);
	rgb.x = ((pixel >> 16) & 0xFF);
	rgb.y = ((pixel >> 8) & 0xFF);
	rgb.z = ((pixel) & 0xFF);
	return (rgb);
}
