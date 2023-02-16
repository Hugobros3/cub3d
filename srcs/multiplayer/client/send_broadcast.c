/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_broadcast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 03:16:31 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 12:48:15 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"
#include "cub3d.h"

static int	send_ping(int s, t_sockaddr_in *servaddr)
{
	char	*data;
	size_t	size;

	data = build_ping_event(&size);
	if (sendto(s, data, size, 0,
			(t_sockaddr *)servaddr, sizeof(t_sockaddr)) < 0)
	{
		perror(RED"Error: "RESET"couldn't send broadcast");
		close(s);
		return (-1);
	}
	return (0);
}

static void	build_available_serv(t_answer_event *e,
	t_sockaddr_in addr, t_list **out)
{
	t_available_server	*serv;

	serv = ft_malloc(sizeof(t_available_server));
	serv->name = ft_strdup(e->server_name);
	serv->p_count = e->players;
	serv->p_max = e->max;
	serv->addr = ft_memdup(&addr, sizeof(t_sockaddr));
	ft_lstadd_back(out, ft_lstnew(serv));
}

static t_list	*recv_answers(int s)
{
	t_list			*out;
	t_answer_event	*e;
	t_sockaddr_in	answer_addr;
	socklen_t		len;
	int				err;

	answer_addr.sin_addr.s_addr = INADDR_ANY;
	answer_addr.sin_family = AF_INET;
	answer_addr.sin_port = htons(BROADCAST_PORT);
	len = sizeof(answer_addr);
	out = NULL;
	err = read_next_event_from(s, (t_event_base **)&e, &answer_addr, &len);
	while (err > 0)
	{
		if (!e)
			continue ;
		if (e->type == ANSWER_EVENT)
			build_available_serv(e, answer_addr, &out);
		free_event((t_event_base *)e);
		err = read_next_event_from(s, (t_event_base **)&e, &answer_addr, &len);
	}
	return (out);
}

t_list	*list_servers(void)
{
	t_sockaddr_in	servaddr;
	t_list			*out;
	int				s;

	s = ls_serv_create_socket(&servaddr);
	if (s < 0)
		return (NULL);
	if (send_ping(s, &servaddr) < 0)
		return (NULL);
	out = recv_answers(s);
	close(s);
	return (out);
}
