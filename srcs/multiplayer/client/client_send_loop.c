/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:49:51 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 08:50:04 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"
#include "raycast.h"

void	*client_send_loop(void *data)
{
	int				n;
	char			*e;
	int				s;
	t_update_event	update_e;
	size_t			size;	

	s = *(int *)data;
	while (get_is_running())
	{
		update_e = (t_update_event){.player_name = g_data.hostname,
			.pos = g_player.pos, .rot = g_player.rot, .height = g_player.height,
			.flashlight = g_data.flashlight};
		e = build_update_event(update_e, &size);
		n = write(s, e, size);
		if (n <= 0)
		{
			free(e);
			client_error("Couldn't send");
			break ;
		}
		free(e);
		usleep(SEND_FREQUENCY);
	}
	client_log("Stopping sending thread...\n");
	return (NULL);
}
