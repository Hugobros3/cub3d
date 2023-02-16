/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplayer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:00:58 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 15:00:35 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer.h"
#include <signal.h>

t_list			*g_threads;
t_list			*g_sockets;
pthread_mutex_t	g_run_m;
t_bool			g_run;
t_server		g_server;
t_image			*g_hider_tex;
t_image			*g_seeker_tex;

void	sig_stop(int s)
{
	(void)s;
	cleanup_multiplayer();
	exit(0);
}

void	init_multiplayer(void)
{
	signal(SIGINT, sig_stop);
	signal(SIGPIPE, SIG_IGN);
	g_threads = NULL;
	g_sockets = NULL;
	g_server.players = NULL;
	g_hider_tex = new_img_file(g_game->mlx, "./assets/rat.xpm");
	g_seeker_tex = new_img_file(g_game->mlx, "./assets/rat.xpm");
	pthread_mutex_init(&g_run_m, NULL);
}

int	sync_read(int s, void *buf, size_t size)
{
	int	ret;

	pthread_mutex_unlock(&g_game->sychro_mutex);
	ret = read(s, buf, size);
	pthread_mutex_lock(&g_game->sychro_mutex);
	return (ret);
}

int	sync_write(int s, void *buf, size_t size)
{
	int	ret;

	pthread_mutex_unlock(&g_game->sychro_mutex);
	ret = write(s, buf, size);
	pthread_mutex_lock(&g_game->sychro_mutex);
	return (ret);
}
