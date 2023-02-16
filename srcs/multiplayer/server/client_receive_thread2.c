/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_receive_thread2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:50:55 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/31 17:22:23 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"

#define ERR "\x1B[31mError: \x1B[0m"

void	handle_error(int err, t_client_instance *i)
{
	if (i)
		server_log(RED"Problem"RESET" with client '"YEL"%s"RESET"'\
			 occurred ! :\n", get_addr_as_str((t_sockaddr *)&(i->addr)));
	else
		server_log(RED"Problem"RESET" with unknown client occurred ! :\n");
	if (err == 0)
		server_log("\t-> Connection seems to be closed...\n");
	if (err == -1 || err == -2)
		server_log("\t-> Read/Write error\n");
	if (err == -3)
		server_log("\t-> Invalid event type !\n");
	if (err == -4)
		server_log("\t-> Invalid event !\n");
}

static void	handle_leave_event(t_leave_event *e)
{
	printf("Received leave event:  %s\n", e->player_name);
	g_server.player_count--;
}

static void	handle_update_event(t_update_event *e)
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
}

int	client_instance_receive_thread2(t_event_base *event,
	t_client_instance *i)
{
	if (event->type == JOIN_EVENT)
		handle_join_event(i, (t_join_event *)event);
	if (event->type == LEAVE_EVENT)
		handle_leave_event((t_leave_event *)event);
	if (event->type == UPDATE_EVENT)
		handle_update_event((t_update_event *)event);
	if (send_to_all(i, event) < 0)
	{
		free_event(event);
		server_log(ERR"Couldn't send to all\n");
		return (-1);
	}
	return (0);
}
