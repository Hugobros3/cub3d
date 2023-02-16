/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_receive_thread.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:27:23 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:38:19 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"

#define ERR "\x1B[31mError: \x1B[0m"

static int	send_to_all2(char **data, size_t *size, t_event_base *e)
{
	*data = NULL;
	if (e->type == JOIN_EVENT)
		*data = build_join_event(*(t_join_event *)e, size);
	else if (e->type == LEAVE_EVENT)
		*data = build_leave_event(*(t_leave_event *)e, size);
	else if (e->type == UPDATE_EVENT)
		*data = build_update_event(*(t_update_event *)e, size);
	else
		return (0);
	return (0);
}

int	send_to_all(t_client_instance *except, t_event_base *e)
{
	char		*data;
	size_t		size;
	t_list		*curr;
	t_m_player	*m_player;

	send_to_all2(&data, &size, e);
	if (!data)
		return (0);
	curr = g_server.players;
	while (curr)
	{
		m_player = (t_m_player *)curr->content;
		if (!ft_memcmp(m_player->i, except, sizeof(t_client_instance)))
		{
			curr = curr->next;
			continue ;
		}
		printf("Send to %s\n", m_player->entity->name);
		if (send(m_player->i->s, data, size, 0) < 0)
			return (-1);
		curr = curr->next;
	}
	free(data);
	return (0);
}

void	*client_instance_receive_thread(void *data)
{
	t_client_instance	*i;
	t_event_base		*event;
	int					err;

	i = (t_client_instance *)data;
	event = NULL;
	while (get_is_running() && i->run)
	{
		err = read_next_event(i->s, &event);
		if (err == 0 || !event)
			continue ;
		if (err < 0)
		{
			handle_error(err, i);
			server_log(ERR"Receive error\n");
			break ;
		}
		if (client_instance_receive_thread2(event, i) < 0)
			break ;
	}
	i->run = FALSE;
	server_log("Stopped client receive thread\n");
	return (NULL);
}
