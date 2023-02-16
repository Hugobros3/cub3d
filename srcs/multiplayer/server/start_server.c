/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:33:49 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 09:57:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"

int	init_serv(int *s)
{
	int				sockfd;
	t_sockaddr_in	addr;	

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		return (server_error("Couldn't create socket"));
	ft_lstadd_back(&g_sockets, ft_lstnew(ft_memdup(&sockfd, sizeof(int))));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(CONNECTION_PORT);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sockfd, (t_sockaddr *)&addr, sizeof(addr)) < 0)
		return (server_error("Couldn't bind socket"));
	if (listen(sockfd, 10) == 0)
		server_log(GRN"Listening for incoming connections !"RESET"\n");
	else
		return (server_error("Couldn't listen !"));
	*s = sockfd;
	return (0);
}

void	start_server(void)
{
	int	s;

	if (g_settings.is_server || g_settings.is_client)
		return ;
	g_data.map_save = NULL;
	g_server.player_count = 0;
	g_server.players = NULL;
	g_run = TRUE;
	if (init_serv(&s) < 0)
		return ;
	if (start_server_main_thread(s) < 0)
		return ;
	g_settings.is_server = TRUE;
	mlxdg_create_entry(g_game, "Player count: ",
		(char *(*)(void *))mlxdg_entry_int, &g_server.player_count);
}
