/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:18:55 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 14:50:41 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"

#define ERR "\x1B[31mError: \x1B[0m"

void	*client_instance_send_thread(void *data)
{
	t_client_instance	*i;
	t_update_event		event;
	char				*package;
	int					n;
	size_t				size;

	i = (t_client_instance *)data;
	while (get_is_running() && i->run)
	{
		event = (t_update_event){.player_name = g_data.hostname,
			.pos = g_player.pos, .rot = g_player.rot,
			.height = g_player.height, .flashlight = g_data.flashlight};
		package = build_update_event(event, &size);
		n = write(i->s, package, size);
		if (n <= 0)
		{
			server_log(ERR"Couldn't send !\n");
			return (NULL);
		}
		usleep(SEND_FREQUENCY);
	}
	i->run = FALSE;
	server_log("Stopped client send thread\n");
	return (NULL);
}
