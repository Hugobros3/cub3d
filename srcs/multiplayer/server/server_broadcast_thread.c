/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_broadcast_thread.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:41:57 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:36:21 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"

static int	make_broadcast_socket(void)
{
	int	s;

	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
		return (-1);
	ft_lstadd_back(&g_sockets, ft_lstnew(ft_memdup(&s, sizeof(int))));
	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
	{
		perror(RED"Error: "RESET"couldn't set sock config");
		close(s);
		return (-1);
	}
	if (set_sock_timeout(s, 1) < 0)
	{
		printf("Sock timeout error\n");
		return (-1);
	}
	return (s);
}

void	handle_ping_event(int s, t_sockaddr_in cliaddr,
	socklen_t len, t_ping_event *e)
{
	t_answer_event	answer_e;
	size_t			size;
	char			*data;
	int				n;

	(void)e;
	answer_e.server_name = g_data.hostname;
	answer_e.players = g_server.player_count;
	answer_e.max = MAX_PLAYERS;
	data = build_answer_event(answer_e, &size);
	n = sendto(s, data, size, MSG_WAITALL, (t_sockaddr *)&cliaddr, len);
	if (n <= 0)
		server_log("Couldn't send answer\n");
	free(data);
}

void	broadcast_loop(int s)
{
	int				err;
	t_ping_event	*event;
	socklen_t		len;
	t_sockaddr_in	cliaddr;

	len = sizeof(t_sockaddr_in);
	ft_memset(&cliaddr, 0, sizeof(t_sockaddr_in));
	while (get_is_running())
	{
		err = read_next_event_from(s, (t_event_base **)&event, &cliaddr, &len);
		if (err <= 0)
			continue ;
		server_log("Received broadcast from '%s'   %d\n",
			get_addr_as_str((t_sockaddr *)&cliaddr), event->type);
		if (!event)
			continue ;
		if (event->type == PING_EVENT)
			handle_ping_event(s, cliaddr, len, (t_ping_event *)event);
		free_event((t_event_base *)event);
	}
}

void	*server_broadcast_thread(void *d)
{
	int				s;
	t_sockaddr_in	servaddr;

	(void)d;
	s = make_broadcast_socket();
	if (s < 0)
	{
		printf("Couldn't make broadcast socket...\n");
		return (NULL);
	}
	ft_memset(&servaddr, 0, sizeof(t_sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(BROADCAST_PORT);
	if (bind(s, (t_sockaddr *)&servaddr,
			sizeof(t_sockaddr)) < 0)
	{
		printf("Couldn't bind broadcast socket\n");
		return (NULL);
	}
	broadcast_loop(s);
	server_log("Broadcast thread stopped !\n");
	return (NULL);
}
