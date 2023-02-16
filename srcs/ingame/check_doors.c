/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_doors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:26:55 by estarck           #+#    #+#             */
/*   Updated: 2023/01/30 12:34:05 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool	is_player_close(t_door door)
{
	return (ft_dist2(g_player.pos, door.pos) <= DOOR_OPEN_RADIUS);
}

static t_bool	is_entity_close(t_door door)
{
	t_list		*curr;
	t_entity	*e;

	curr = g_data.multiplayer_entities;
	while (curr)
	{
		e = (t_entity *)curr->content;
		if (ft_dist2(e->pos, door.pos) <= DOOR_OPEN_RADIUS)
			return (TRUE);
		curr = curr->next;
	}
	return (FALSE);
}

void	update_door_open(t_door *d)
{
	if (d->open_amount < 1)
	{
		d->open_amount += g_game->d_time * DOOR_OPEN_SPEED / 3;
		if (d->open_amount > 1)
			d->open_amount = 1;
	}
}

void	update_door_close(t_door *d)
{
	if (d->open_amount > 0)
	{
		d->open_amount -= g_game->d_time * DOOR_OPEN_SPEED / 3;
		if (d->open_amount < 0)
			d->open_amount = 0;
	}
}

void	update_doors(void)
{
	t_door	*doors;
	int		i;

	i = 0;
	doors = g_map.doors;
	while (i < g_map.doors_size)
	{
		if (is_player_close(doors[i]) || ((g_settings.is_server
					|| g_settings.is_client) && is_entity_close(doors[i])))
			update_door_open(&doors[i]);
		else
			update_door_close(&doors[i]);
		i++;
	}
}
