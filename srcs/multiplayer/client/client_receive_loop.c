/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_receive_loop.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:34:39 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 09:48:16 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"
#include "raycast.h"

static void	client_handle_join_event(t_join_event *event)
{
	printf("Received join event\n");
	register_new_player(event, NULL);
}

static void	client_handle_leave_event(t_leave_event *event)
{
	t_list				*elem;
	t_m_player			*i;

	printf("Received leave event\n");
	elem = ft_lstfind(g_server.players, cmp_player_instance,
			event->player_name);
	if (!elem)
		return ;
	i = (t_m_player *)elem->content;
	if (i->flashlight)
		remove_light(i->flashlight);
}

static void	client_handle_update_event(t_update_event *e)
{
	t_list				*elem;
	t_m_player			*i;

	elem = ft_lstfind(g_server.players, cmp_player_instance, e->player_name);
	if (!elem)
		return ;
	i = (t_m_player *)elem->content;
	i->entity->height = e->height;
	i->entity->pos = e->pos;
	i->entity->rotation = e->rot;
	if (i->flashlight)
	{
		if (e->flashlight)
			i->flashlight->size = 10;
		else
			i->flashlight->size = 0;
		i->flashlight->pos = v4(i->entity->pos.x, i->entity->height,
				i->entity->pos.y, 0);
		i->flashlight->dir = v4(-cos(ft_radians(i->entity->rotation)), 0,
				-sin(ft_radians(i->entity->rotation)), 0);
	}
}

static void	client_receive_loop2(t_event_base *event)
{
	if (event->type == JOIN_EVENT)
		client_handle_join_event((t_join_event *)event);
	if (event->type == LEAVE_EVENT)
		client_handle_leave_event((t_leave_event *)event);
	if (event->type == UPDATE_EVENT)
		client_handle_update_event((t_update_event *)event);
}

void	*client_receive_loop(void *data)
{
	int				err;
	int				s;
	t_event_base	*event;

	s = *(int *)data;
	event = NULL;
	while (get_is_running())
	{
		err = read_next_event(s, &event);
		if (err == 0 || !event)
			continue ;
		if (err < 0)
		{
			handle_error_client(err);
			client_error("Receive error");
			break ;
		}
		client_receive_loop2(event);
		free_event(event);
	}
	client_log("Stopping receive thread...\n");
	return (NULL);
}
