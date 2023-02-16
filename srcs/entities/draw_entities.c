/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 23:45:35 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 15:56:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_3d.h"
#include "cub3d.h"
#include "raycast.h"

void	reset_d_buffer(void)
{
	mlxcl_exec_kernel2(g_game, g_renderer_3d.reset_d_buffer,
		iv2(8, 8), iv2(PROJ_SIZE, PROJ_SIZE));
}

t_bool	is_on_screen(t_iv2 start, t_iv2 end)
{
	if ((start.x < 0 && end.x < 0)
		|| (start.x >= g_game->size.x && end.x >= g_game->size.x)
		|| (start.y < 0 && end.y < 0)
		|| (start.y >= g_game->size.y && end.y >= g_game->size.y))
		return (FALSE);
	return (TRUE);
}

void	draw_entities(void)
{
	t_list		*curr;
	t_entity	*e;
	t_iv2		draw_start;
	t_iv2		draw_end;

	if (g_settings.is_server || g_settings.is_client)
		curr = g_data.multiplayer_entities;
	else
		curr = g_data.entities;
	while (curr)
	{
		e = curr->content;
		get_sprite_pos(e, &draw_start, &draw_end);
		if (is_on_screen(draw_start, draw_end))
		{
			reset_d_buffer();
			projection(e);
			drawing(e, draw_start, draw_end);
		}
		curr = curr->next;
	}
}
