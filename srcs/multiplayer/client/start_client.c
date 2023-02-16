/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_client.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:30:00 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 08:49:20 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"

int	init_client(char *ip, int *s, t_sockaddr_in *addr)
{
	int				sockfd;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		return (client_error("Couldn't create socket"));
	ft_lstadd_back(&g_sockets, ft_lstnew(ft_memdup(&sockfd, sizeof(int))));
	client_log("Socket created ("YEL"%d"RESET")\n", sockfd);
	addr->sin_family = AF_INET;
	addr->sin_port = htons(CONNECTION_PORT);
	addr->sin_addr.s_addr = inet_addr(ip);
	*s = sockfd;
	return (0);
}

void	start_client(char *ip)
{
	int				s;
	t_sockaddr_in	addr;

	s = -1;
	if (g_settings.is_client || g_settings.is_server)
		return ;
	g_run = TRUE;
	if (init_client(ip, &s, &addr) < 0)
		return ;
	if (start_client_main_thread(s, addr) < 0)
		return ;
	g_settings.is_client = TRUE;
	mlxdg_create_entry(g_game, "Player count: ",
		(char *(*)(void *))mlxdg_entry_int, &g_server.player_count);
}
