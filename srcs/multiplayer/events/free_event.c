/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:24:36 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 08:25:55 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events_builder.h"
#include "../multiplayer.h"

void	free_update_event(t_update_event *e)
{
	free(e->player_name);
	free(e);
}

void	free_join_event(t_join_event *e)
{
	free(e->player_name);
	free(e);
}

void	free_leave_event(t_leave_event *e)
{
	free(e->player_name);
	free(e);
}

void	free_ping_event(t_ping_event *e)
{
	free(e);
}

void	free_answer_event(t_answer_event *e)
{
	free(e->server_name);
	free(e);
}
