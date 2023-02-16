/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 23:28:36 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/25 23:31:59 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine_int.h"
#include "mlx_engine.h"

static t_color	make_color(t_image *dest,
				t_image *src, t_iv2 xy_scaled, t_v2 uv)
{
	t_color	old_col;
	t_color	new_col;
	t_color	out;
	float	new_a;
	float	old_a;

	old_col = getpixel(dest, xy_scaled.x, xy_scaled.y);
	new_col = sample_texture(src, uv);
	new_a = ft_invlerp(0, 255, new_col.w);
	old_a = ft_invlerp(0, 255, new_col.w);
	out = new_color(
			new_a * new_col.x + (1 - new_a) * old_col.x * old_a,
			new_a * new_col.y + (1 - new_a) * old_col.y * old_a,
			new_a * new_col.z + (1 - new_a) * old_col.z * old_a,
			(new_a + old_a * (1 - new_a)) * 255
			);
	return (out);
}

void	overlay_image(t_image *dest, t_image *src, t_iv2 pos, t_v2 scale)
{
	t_iv2	xy;
	t_v2	uv;
	t_iv2	xy_scaled;

	xy = pos;
	while (xy.x < pos.x + src->size->x)
	{
		xy.y = pos.y;
		while (xy.y < pos.y + src->size->y)
		{
			xy_scaled = iv2((int)(xy.x * scale.x), (int)(xy.y * scale.y));
			uv = v2(
					ft_invlerp(pos.x * scale.x,
						(pos.x + src->size->x) * scale.x, xy_scaled.x),
					ft_invlerp(pos.y * scale.y,
						(pos.y + src->size->y) * scale.y, xy_scaled.y)
					);
			putpixel(dest, xy_scaled.x, xy_scaled.y,
				make_color(dest, src, xy_scaled, uv));
			xy.y++;
		}
		xy.x++;
	}
}
