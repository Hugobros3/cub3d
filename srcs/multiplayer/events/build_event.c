/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:09:45 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 08:27:05 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"
#include "events_builder.h"

static char	*base_event(char *e_type, char *player_name)
{
	char	*out;

	out = ft_strdup(e_type);
	out = ft_str_append(out, " ", 1, 0);
	out = ft_str_append(out, player_name, 1, 0);
	out = ft_str_append(out, " ", 1, 0);
	return (out);
}

void	*finish_event(char *e, size_t *out_size)
{
	int		size;
	void	*out;

	size = ft_strlen(e) + 1;
	out = ft_malloc(sizeof(char) * size + sizeof(int));
	ft_bzero(out, size * sizeof(char) + sizeof(int));
	*(int *)out = size;
	ft_memcpy(out + sizeof(int), e, sizeof(char) * size);
	free(e);
	*out_size = size * sizeof(char) + sizeof(int);
	return (out);
}

char	*build_join_event(t_join_event e, size_t *size)
{
	char	*out;

	out = base_event(BASE_JOIN_EVENT, e.player_name);
	out = ft_str_append(out, ft_itoa((int)e.t), 1, 1);
	return (finish_event(out, size));
}

char	*build_leave_event(t_leave_event e, size_t *size)
{
	char	*out;

	out = base_event(BASE_LEAVE_EVENT, e.player_name);
	return (finish_event(out, size));
}

char	*build_update_event(t_update_event e, size_t *size)
{
	char	*out;

	out = base_event(BASE_UPDATE_EVENT, e.player_name);
	out = ft_str_append(out, float_to_char(e.pos.x), 1, 1);
	out = ft_str_append(out, " ", 1, 0);
	out = ft_str_append(out, float_to_char(e.pos.y), 1, 1);
	out = ft_str_append(out, " ", 1, 0);
	out = ft_str_append(out, float_to_char(e.rot), 1, 1);
	out = ft_str_append(out, " ", 1, 0);
	out = ft_str_append(out, float_to_char(e.height), 1, 1);
	out = ft_str_append(out, " ", 1, 0);
	out = ft_str_append(out, ft_itoa((int)e.flashlight), 1, 1);
	return (finish_event(out, size));
}
