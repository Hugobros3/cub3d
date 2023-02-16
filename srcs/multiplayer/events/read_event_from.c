/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_event_from.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:29:22 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 18:44:09 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events_builder.h"
#include "../multiplayer.h"

int	read_event_size_from(int s, t_sockaddr_in *addr, socklen_t *len)
{
	int	n;
	int	out;

	n = recvfrom(s, &out, sizeof(int), 0, (t_sockaddr *)addr, len);
	if (n <= 0)
		return (n);
	return (out);
}

static char	*receive_str(int s, t_sockaddr *addr, socklen_t *len)
{
	char	*str;
	char	tmp[MAX_UDP_SIZE + 1];
	int		n;

	ft_bzero(tmp, sizeof(char) * (MAX_UDP_SIZE + 1));
	n = recvfrom(s, tmp, sizeof(char) * MAX_UDP_SIZE, 0, addr, len);
	tmp[n] = '\0';
	if (n < 4)
		return (NULL);
	str = ft_strdup(tmp + 4);
	if (n <= 0)
		return (NULL);
	return (str);
}

int	read_next_event_from(int s, t_event_base **e,
	t_sockaddr_in *addr, socklen_t *len)
{
	char			*str_received;
	char			**split;
	t_event_type	type;

	str_received = receive_str(s, (t_sockaddr *)addr, len);
	if (!str_received)
		return (-5);
	split = ft_split(str_received, ' ');
	free(str_received);
	type = parse_event_type(split[0]);
	if (type < 0 || parse_event(type, split + 1, e) < 0)
	{
		printf("--> Last event: %s\n", str_received);
		ft_freesplit(split);
		return (-3);
	}
	ft_freesplit(split);
	return (1);
}
