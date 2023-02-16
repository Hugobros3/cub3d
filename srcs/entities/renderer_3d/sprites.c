/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:13:17 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 15:54:54 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycast.h"

t_v4	get_sprite_rot(t_entity *e)
{
	t_v3	s_relative_pos;
	t_v4	rot;

	s_relative_pos = sub3(v3(e->pos.x, e->height, e->pos.y),
			v3(g_player.pos.x, g_player.height, g_player.pos.y));
	rot.y = -atan2(-s_relative_pos.z, s_relative_pos.x)
		+ ft_radians(360 - e->rotation);
	rot.z = 0;
	rot.x = 0;
	rot.w = 0;
	return (rot);
}

static float	get_sprite_pos2(t_entity *e)
{
	t_v2	s_relative_pos;
	float	theta_temp;
	float	theta;
	float	y_tmp;

	s_relative_pos = sub2(e->pos, g_player.pos);
	theta_temp = ft_degrees(atan2(-s_relative_pos.y, s_relative_pos.x));
	if (theta_temp < 0)
		theta_temp += 360;
	theta = ft_fwrap(-g_player.rot - 30, 0, 360) + 30 - g_player.fov / 2;
	y_tmp = theta + 60 - theta_temp;
	if (theta_temp > 270 && theta < 90)
		y_tmp = theta + 60 - theta_temp + 360;
	if (theta > 270 && theta_temp < 90)
		y_tmp = theta + 60 - theta_temp - 360;
	return (y_tmp * g_game->size.x / g_player.fov);
}

static void	get_sprite_pos3(t_entity *e, t_v2 *size, float *y_offset)
{
	float	dist;

	dist = ft_dist2(e->pos, g_player.pos);
	size->x = g_game->size.y / 2 / dist * 5;
	size->y = g_game->size.y / 2 / dist * 4;
	*y_offset = (250 / dist) + (g_player.up_rot) * 300 - (
			(g_player.height - 0.5f - (e->height - e->is_rat * 0.7))
			* 300 / dist * 2);
}

void	get_sprite_pos(t_entity *e, t_iv2 *start_pos, t_iv2 *end_pos)
{
	float	x_tmp;
	t_v2	size;
	float	y_offset;
	t_v2	start;
	t_v2	end;

	x_tmp = get_sprite_pos2(e);
	get_sprite_pos3(e, &size, &y_offset);
	start.x = x_tmp - size.x / 2;
	start.y = (g_game->size.y / 2 - size.y / 2) - y_offset;
	end.x = x_tmp + size.x / 2;
	end.y = (g_game->size.y / 2 + size.y / 2) - y_offset;
	*start_pos = v2iv2(start);
	*end_pos = v2iv2(end);
}
