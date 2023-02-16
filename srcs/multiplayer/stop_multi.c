/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:47:43 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/31 17:02:41 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "multiplayer.h"
#include "raycast.h"

static t_bool			g_stop_request = FALSE;
static pthread_mutex_t	g_stop_request_m = PTHREAD_MUTEX_INITIALIZER;

void	stop_multi_loop(t_game *g)
{
	t_bool	stop;

	(void)g;
	pthread_mutex_lock(&g_stop_request_m);
	pthread_mutex_lock(&g_run_m);
	stop = (g_stop_request && g_run);
	pthread_mutex_unlock(&g_run_m);
	pthread_mutex_unlock(&g_stop_request_m);
	if (stop)
	{
		stop_multiplayer();
		pthread_mutex_lock(&g_stop_request_m);
		g_stop_request = FALSE;
		pthread_mutex_unlock(&g_stop_request_m);
	}
}

void	request_multi_stop(void)
{
	pthread_mutex_lock(&g_stop_request_m);
	g_stop_request = TRUE;
	pthread_mutex_unlock(&g_stop_request_m);
}

static void	stop_multiplayer2(void)
{
	t_map	*new;

	g_settings.is_client = FALSE;
	g_settings.is_server = FALSE;
	g_server.player_count = 0;
	if (g_data.map_save)
	{
		pthread_mutex_lock(&g_raycast.map_buffer_m);
		printf("Free map copy...\n");
		pthread_mutex_lock(&g_game->sychro_mutex);
		new = duplicate_map(g_data.map_save);
		pthread_mutex_unlock(&g_game->sychro_mutex);
		cleanup_map(&g_map);
		ft_memcpy(&g_map, new, sizeof(t_map));
		free(new);
		raycast_init();
		init_renderer();
		pthread_mutex_unlock(&g_raycast.map_buffer_m);
	}
}

void	stop_multiplayer(void)
{
	static t_bool	stop;

	printf("\nMultiplayer stop requested\n");
	if (stop)
		return ;
	stop = TRUE;
	pthread_mutex_lock(&g_run_m);
	g_run = FALSE;
	pthread_mutex_unlock(&g_run_m);
	ft_lstclear(&g_server.players, free_m_player);
	g_data.multiplayer_entities = NULL;
	printf("	->Closing sockets...\n");
	ft_lstclear(&g_sockets, free_sock);
	printf("	->Waiting for threads for finish...\n");
	ft_lstclear(&g_threads, free_thread);
	pthread_mutex_unlock(&g_game->sychro_mutex);
	stop_multiplayer2();
	mlxdg_remove_entry(g_game, "Player count: ");
	pthread_mutex_unlock(&g_game->sychro_mutex);
	printf("Done !\n");
	stop = FALSE;
	load_menu();
}
