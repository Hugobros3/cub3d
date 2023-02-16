/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:43:35 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 15:41:31 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"

static t_client_instance	*new_client_instance(t_sockaddr_in addr, int s)
{
	t_client_instance	*i;

	i = ft_malloc(sizeof(t_client_instance));
	i->addr = addr;
	i->s = s;
	return (i);
}

int	timeout_accept(int sockfd, struct sockaddr *addr,
	socklen_t *addrlen, int timeout)
{
	fd_set			set;
	struct timeval	tv;
	int				rv;

	rv = 1;
	while (rv >= 0 && get_is_running())
	{
		FD_ZERO(&set);
		FD_SET(sockfd, &set);
		tv.tv_sec = timeout;
		tv.tv_usec = 0;
		rv = select(sockfd + 1, &set, NULL, NULL, &tv);
		if (rv == -1)
			return (-1);
		else if (rv == 0)
			continue ;
		else
			return (accept(sockfd, addr, addrlen));
	}
	return (0);
}

static int	server_main_thread2(t_sockaddr_in cli_addr, int cli_s)
{
	t_client_instance	*i;
	pthread_t			thread;

	ft_lstadd_back(&g_sockets, ft_lstnew(
			ft_memdup(&cli_s, sizeof(int))));
	i = new_client_instance(cli_addr, cli_s);
	if (pthread_create(&thread, NULL, client_instance_thread, i) != 0)
	{
		ft_lstremoveif(&g_sockets, NULL, ft_cmpint, &cli_s);
		close(cli_s);
		server_error("Couldn't create client instance thread !");
		return (-1);
	}
	server_log(YEL"Someone"RESET" connected to server !\n");
	ft_lstadd_back(&g_threads, ft_lstnew(
			ft_memdup(&thread, sizeof(pthread_t))));
	return (0);
}

void	*server_main_thread(void *s)
{
	int					client_sock;
	t_sockaddr_in		client_addr;
	socklen_t			sock_len;

	while (get_is_running())
	{
		server_log("Waiting for connection...\n");
		ft_bzero(&client_addr, sizeof(t_sockaddr));
		sock_len = 0;
		client_sock = timeout_accept(*(int *)s,
				(t_sockaddr *)&client_addr, &sock_len, 1);
		if (client_sock == 0)
			break ;
		if (client_sock < 0)
		{
			server_log("Couldn't accept connection\n");
			continue ;
		}
		if (server_main_thread2(client_addr, client_sock) < 0)
			continue ;
	}
	server_log("Server main thread stopped\n");
	free(s);
	return (NULL);
}

int	start_server_main_thread(int s)
{
	pthread_t	listen_thread_id;
	pthread_t	broadcast_thread_id;

	if (pthread_create(&listen_thread_id, NULL, server_main_thread,
			ft_memdup(&s, sizeof(int))) != 0)
		return (server_error("Couldn't create server thread !"));
	ft_lstadd_back(&g_threads, ft_lstnew(ft_memdup(&listen_thread_id,
				sizeof(pthread_t))));
	server_log("Created server thread\n");
	if (pthread_create(&broadcast_thread_id, NULL, server_broadcast_thread,
			NULL) != 0)
		return (server_error("Couldn't create broadcast listen thread !"));
	ft_lstadd_back(&g_threads, ft_lstnew(ft_memdup(&broadcast_thread_id,
				sizeof(pthread_t))));
	server_log("Created broadcast listen thread\n");
	return (0);
}
