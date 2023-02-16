/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:39:35 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:42:37 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"
#include "raycast.h"

void	handle_error_client(int err)
{
	client_log(RED"Problem"RESET" with "YEL"server"RESET" occurred ! :\n");
	if (err == 0)
		client_log("\t-> Connection seems to be closed...\n");
	if (err == -1 || err == -2)
		client_log("\t-> Read/Write error\n");
	if (err == -3)
		client_log("\t-> Invalid event type !\n");
	if (err == -4)
		client_log("\t-> Invalid event !\n");
}

static int	client_connect(int s, t_sockaddr_in addr)
{
	int		err;

	client_log("Connecting through socket '"YEL"%d"RESET"' at addr %s...\n",
		s, get_addr_as_str((t_sockaddr *)&(addr)));
	err = connect(s, (struct sockaddr *)&addr, sizeof(addr));
	if (err == -1)
		return (client_error("Couldn't connect\n"));
	client_log("Connected to %s !\n", get_addr_as_str((t_sockaddr *)&addr));
	return (0);
}

static int	init_client_main_thread(void *data, int s, t_sockaddr_in addr)
{
	if (set_sock_timeout(s, 3) < 0)
	{
		client_error("Sockopt error");
		free(data);
		return (-1);
	}
	if (client_connect(s, addr))
	{
		client_error("Can't connect");
		free(data);
		return (-1);
	}
	pthread_mutex_lock(&g_game->sychro_mutex);
	if (receive_map(s) < 0)
	{
		client_error("Can't receive map");
		free(data);
		return (-1);
	}
	pthread_mutex_unlock(&g_game->sychro_mutex);
	return (0);
}

static int	client_create_threads(pthread_t *send_thread,
	pthread_t *receive_thread, void *data)
{
	if (pthread_create(send_thread, NULL, client_send_loop, data) != 0)
	{
		free(data);
		client_error("Couldn't create client send thread !");
		return (-1);
	}
	client_log("Created client send thread\n");
	if (pthread_create(receive_thread, NULL, client_receive_loop, data) != 0)
	{
		free(data);
		client_error("Couldn't create client receive thread !");
		return (-1);
	}
	client_log("Created client receive thread\n");
	return (0);
}

void	*client_main_thread(void *data)
{
	pthread_t		send_thread;
	pthread_t		receive_thread;
	size_t			size;
	char			*e;

	if (init_client_main_thread(data, *(int *)data,
			*(t_sockaddr_in *)(data + sizeof(int))) < 0)
		return (NULL);
	e = build_join_event((t_join_event){JOIN_EVENT, g_data.hostname, HIDER},
			&size);
	if (write(*(int *)data, e, size) < 0)
	{
		free(data);
		return (NULL);
	}
	free(e);
	if (client_create_threads(&send_thread, &receive_thread, data) < 0)
		return (NULL);
	pthread_join(send_thread, NULL);
	pthread_join(receive_thread, NULL);
	free(data);
	client_log("Stopping client thread !\n");
	return (NULL);
}
