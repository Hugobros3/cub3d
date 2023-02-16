/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_multi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:41:56 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:36:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "multiplayer.h"
#include "raycast.h"

void	cleanup_multiplayer(void)
{
	static t_bool	stop;

	if (stop)
		return ;
	stop = TRUE;
	pthread_mutex_lock(&g_run_m);
	g_run = FALSE;
	pthread_mutex_unlock(&g_run_m);
	printf("\nMultiplayer stop requested\n");
	g_settings.is_client = FALSE;
	g_settings.is_server = FALSE;
	g_server.player_count = 0;
	printf("	->Closing sockets...\n");
	ft_lstclear(&g_sockets, free_sock);
	printf("	->Waiting for threads for finish...\n");
	ft_lstclear(&g_threads, free_thread_force);
}
