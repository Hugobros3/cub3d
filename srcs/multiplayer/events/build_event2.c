/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_event2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:09:45 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 08:23:40 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"
#include "events_builder.h"

char	*build_ping_event(size_t *size)
{
	char	*out;

	out = ft_strdup(BASE_PING_EVENT);
	return (finish_event(out, size));
}

char	*build_answer_event(t_answer_event e, size_t *size)
{
	char	*out;

	out = ft_strdup(BASE_ANSWER_EVENT);
	out = ft_str_append(out, " ", 1, 0);
	out = ft_str_append(out, e.server_name, 1, 0);
	out = ft_str_append(out, " ", 1, 0);
	out = ft_str_append(out, ft_itoa(e.players), 1, 0);
	out = ft_str_append(out, " ", 1, 0);
	out = ft_str_append(out, ft_itoa(e.max), 1, 0);
	return (finish_event(out, size));
}
