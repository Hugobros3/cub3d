/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:12:20 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 15:08:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MOVEMENT_SPEED 2
#define GRAVITY 10

#define MOUSE_SENSITIVITY 5

static void	handle_jump(void)
{
	static float	vertical_vel = 0;

	if (is_key_down(g_game, KEY_SPACE) && vertical_vel == 0)
		vertical_vel = g_settings.vertical_vel;
	if (vertical_vel <= 0 && g_player.height <= g_settings.player_height)
	{
		vertical_vel = 0;
		g_player.height = g_settings.player_height;
	}
	else
	{
		vertical_vel -= g_game->d_time * GRAVITY;
		g_player.height += vertical_vel * g_game->d_time;
	}
}

static void	update_rotation(void)
{
	if (is_key_pressed(g_game, KEY_LEFT))
		g_player.rot -= g_game->d_time * g_settings.mouse_sensi * 2.6;
	if (is_key_pressed(g_game, KEY_RIGHT))
		g_player.rot += g_game->d_time * g_settings.mouse_sensi * 2.6;
	g_player.rot = ft_fwrap(g_player.rot, 0, 360);
	if (is_key_pressed(g_game, KEY_E))
		g_player.up_rot += g_game->d_time * g_settings.mouse_sensi / 20;
	if (is_key_pressed(g_game, KEY_Q))
		g_player.up_rot -= g_game->d_time * g_settings.mouse_sensi / 20;
}

static void	move_player(float dir, t_v2 *p_sc)
{
	p_sc->x += cos(ft_radians(g_player.rot + dir))
		* g_game->d_time * MOVEMENT_SPEED;
	p_sc->y += sin(ft_radians(g_player.rot + dir))
		* g_game->d_time * MOVEMENT_SPEED;
}

static int	collisions_check(t_v2 pos)
{
	if (g_map.data[((int)pos.x + (int)pos.y
				* g_map.size.x)] != WALL)
		return (1);
	else
		return (0);
}

void	update_player(void)
{
	t_v2	p_sc;
	t_v2	next_pos;

	p_sc.x = 0;
	p_sc.y = 0;
	if (is_key_pressed(g_game, KEY_W))
		move_player(0, &p_sc);
	if (is_key_pressed(g_game, KEY_A))
		move_player(-90, &p_sc);
	if (is_key_pressed(g_game, KEY_S))
		move_player(-180, &p_sc);
	if (is_key_pressed(g_game, KEY_D))
		move_player(90, &p_sc);
	next_pos = add2(g_player.pos, v2(0, p_sc.y));
	if (collisions_check(next_pos))
		g_player.pos = next_pos;
	next_pos = add2(g_player.pos, v2(p_sc.x, 0));
	if (collisions_check(next_pos))
		g_player.pos = next_pos;
	handle_jump();
	update_rotation();
	handle_mouse_control();
}
