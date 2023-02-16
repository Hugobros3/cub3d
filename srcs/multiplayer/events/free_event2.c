/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_event2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:25:29 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 08:25:44 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events_builder.h"
#include "../multiplayer.h"

void	free_event(t_event_base *e)
{
	if (e->type == UPDATE_EVENT)
		free_update_event((t_update_event *)e);
	if (e->type == JOIN_EVENT)
		free_join_event((t_join_event *)e);
	if (e->type == LEAVE_EVENT)
		free_leave_event((t_leave_event *)e);
	if (e->type == PING_EVENT)
		free_ping_event((t_ping_event *)e);
	if (e->type == ANSWER_EVENT)
		free_answer_event((t_answer_event *)e);
}
