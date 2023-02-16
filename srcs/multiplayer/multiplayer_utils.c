/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplayer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:57:31 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 15:00:15 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer.h"

int	set_sock_timeout(int s, int time)
{
	struct timeval	timeout;

	timeout.tv_sec = time;
	timeout.tv_usec = 0;
	if (setsockopt (s, SOL_SOCKET, SO_RCVTIMEO, &timeout,
			sizeof timeout) < 0)
		return (-1);
	return (0);
}

char	*get_addr_as_str(t_sockaddr *addr)
{
	static char	addr_str[INET_ADDRSTRLEN];

	inet_ntop(AF_INET, &((t_sockaddr_in *)addr)->sin_addr,
		addr_str, INET_ADDRSTRLEN);
	return (addr_str);
}

t_bool	get_is_running(void)
{
	t_bool	run;

	pthread_mutex_lock(&g_run_m);
	run = g_run;
	pthread_mutex_unlock(&g_run_m);
	return (run);
}
