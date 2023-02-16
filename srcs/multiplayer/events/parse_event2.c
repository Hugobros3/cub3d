/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_event2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:30:56 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 08:31:47 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"
#include "events_builder.h"

t_event_type	parse_event_type(char *e)
{
	if (!ft_strncmp(e, BASE_UPDATE_EVENT, ft_strlen(BASE_UPDATE_EVENT)))
		return (UPDATE_EVENT);
	if (!ft_strncmp(e, BASE_JOIN_EVENT, ft_strlen(BASE_JOIN_EVENT)))
		return (JOIN_EVENT);
	if (!ft_strncmp(e, BASE_LEAVE_EVENT, ft_strlen(BASE_LEAVE_EVENT)))
		return (LEAVE_EVENT);
	if (!ft_strncmp(e, BASE_PING_EVENT, ft_strlen(BASE_PING_EVENT)))
		return (PING_EVENT);
	if (!ft_strncmp(e, BASE_ANSWER_EVENT, ft_strlen(BASE_ANSWER_EVENT)))
		return (ANSWER_EVENT);
	return (-1);
}

int	parse_event(t_event_type t, char **split, t_event_base **e)
{
	int	err;

	err = 0;
	if (t == UPDATE_EVENT)
		err = parse_update_event(split, (t_update_event **)e);
	if (t == JOIN_EVENT)
		err = parse_join_event(split, (t_join_event **)e);
	if (t == LEAVE_EVENT)
		err = parse_leave_event(split, (t_leave_event **)e);
	if (t == PING_EVENT)
		err = parse_ping_event(split, (t_ping_event **)e);
	if (t == ANSWER_EVENT)
		err = parse_answer_event(split, (t_answer_event **)e);
	if (err < 0)
		return (-1);
	return (0);
}
