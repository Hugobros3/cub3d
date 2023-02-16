/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:06:34 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 08:31:09 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"
#include "events_builder.h"

int	parse_join_event(char **e, t_join_event **event)
{
	if (ft_splitlen(e) != 2)
		return (-1);
	(*event) = ft_malloc(sizeof(t_join_event));
	(*event)->type = JOIN_EVENT;
	(*event)->player_name = ft_strdup(e[0]);
	(*event)->t = ft_atoi(e[1]);
	return (0);
}

int	parse_leave_event(char **e, t_leave_event **event)
{
	if (ft_splitlen(e) != 1)
		return (-1);
	(*event) = ft_malloc(sizeof(t_leave_event));
	(*event)->type = LEAVE_EVENT;
	(*event)->player_name = ft_strdup(e[0]);
	return (0);
}

int	parse_update_event(char **e, t_update_event **event)
{
	if (ft_splitlen(e) != 6)
		return (-1);
	(*event) = ft_malloc(sizeof(t_update_event));
	(*event)->type = UPDATE_EVENT;
	(*event)->player_name = ft_strdup(e[0]);
	(*event)->pos.x = char_to_float(e[1]);
	(*event)->pos.y = char_to_float(e[2]);
	(*event)->rot = char_to_float(e[3]);
	(*event)->height = char_to_float(e[4]);
	(*event)->flashlight = ft_atoi(e[5]);
	return (0);
}

int	parse_ping_event(char **e, t_ping_event **event)
{
	if (ft_splitlen(e) != 0)
		return (-1);
	(*event) = ft_malloc(sizeof(t_ping_event));
	(*event)->type = PING_EVENT;
	return (0);
}

int	parse_answer_event(char **e, t_answer_event **event)
{
	if (ft_splitlen(e) != 3)
		return (-1);
	(*event) = ft_malloc(sizeof(t_answer_event));
	(*event)->type = ANSWER_EVENT;
	(*event)->server_name = ft_strdup(e[0]);
	(*event)->players = ft_atoi(e[1]);
	(*event)->max = ft_atoi(e[2]);
	return (0);
}
