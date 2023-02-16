/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_broadcast2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 03:16:31 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 12:48:12 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"
#include "cub3d.h"

void	free_t_available_server(t_available_server *s)
{
	free(s->addr);
	free(s->name);
	free(s);
}

static int	config_socket(int s)
{
	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
	{
		perror(RED"Error: "RESET"couldn't set sock config");
		close(s);
		return (-1);
	}
	if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, &(int){1}, sizeof(int)) < 0)
	{
		perror(RED"Error: "RESET"couldn't set sock config");
		close(s);
		return (-1);
	}
	if (set_sock_timeout(s, 1))
	{
		perror(RED"Error: "RESET"couldn't set sock timeout");
		close(s);
		return (-1);
	}
	return (0);
}

int	ls_serv_create_socket(t_sockaddr_in *addr)
{
	int				s;
	t_sockaddr_in	servaddr;

	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
	{
		perror(RED"Error: "RESET"couldn't create broadcast socket");
		return (-1);
	}
	ft_memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(BROADCAST_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	if (config_socket(s) < 0)
		return (-1);
	*addr = servaddr;
	return (s);
}
