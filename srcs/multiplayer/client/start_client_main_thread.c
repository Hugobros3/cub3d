/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_client_main_thread.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:45:06 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 12:49:23 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"
#include "raycast.h"

int	start_client_main_thread(int s, t_sockaddr_in addr)
{
	pthread_t	thread;
	void		*data;

	data = ft_malloc(sizeof(int) + sizeof(t_sockaddr_in));
	(*(int *)data) = s;
	(*(t_sockaddr_in *)(data + sizeof(int))) = addr;
	if (pthread_create(&thread, NULL, client_main_thread, data) != 0)
		return (client_error("Couldn't create client thread !"));
	client_log("Created client thread\n");
	ft_lstadd_back(&g_threads, ft_lstnew(
			ft_memdup(&thread, sizeof(pthread_t))));
	return (0);
}
