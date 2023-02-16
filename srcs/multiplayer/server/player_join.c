/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:26:17 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:38:29 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"

static int	send_all_players(t_client_instance *i, t_join_event *join_event)
{
	t_list				*curr;
	char				*e;
	t_m_player			*p;
	t_join_event		event;
	size_t				size;

	(void)join_event;
	curr = g_server.players;
	while (curr)
	{
		p = (t_m_player *)curr->content;
		event = (t_join_event){.player_name = p->entity->name,
			.t = p->entity->is_rat};
		e = build_join_event(event, &size);
		if (write(i->s, e, size) < 0)
			return (-1);
		free(e);
		curr = curr->next;
	}
	return (0);
}

void	handle_join_event(t_client_instance *i, t_join_event *e)
{
	size_t			size;
	t_join_event	event;
	char			*str;

	printf("Received join event:  %s %d\n", e->player_name, e->t);
	g_server.player_count++;
	event = (t_join_event){.player_name = g_data.hostname, .t = SEEKER};
	str = build_join_event(event, &size);
	if (write(i->s, str, size) < 0)
		return ;
	send_all_players(i, e);
	register_new_player(e, i);
}
