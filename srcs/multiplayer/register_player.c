/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:58:26 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 15:37:20 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer.h"

int	cmp_player_instance(void *p1, void *p2)
{
	return (!ft_strcmp(((t_m_player *)p1)->entity->name, (char *)p2));
}

static void	register_new_player2(t_join_event *event, t_m_player *new_p,
	t_entity **e)
{
	if (event->t == HIDER)
	{
		*e = create_entity("./assets/rat.obj", g_hider_tex, TRUE);
		new_p->flashlight = NULL;
	}
	else
	{
		*e = create_entity("./assets/rat.obj", g_seeker_tex, FALSE);
		new_p->flashlight = add_light((t_light){v4(0, 0, 0, 0), v4(1, 1, 1, 1),
				v4(0, 0, 0, 0), 20, 11, TRUE});
	}
}

void	register_new_player(t_join_event *event, t_client_instance *i)
{
	t_m_player	*new_p;
	t_entity	*e;

	if (ft_lstfind(g_server.players, cmp_player_instance, event->player_name))
		return ;
	new_p = ft_malloc(sizeof(t_m_player));
	printf("Adding entity...\n");
	pthread_mutex_lock(&g_game->sychro_mutex);
	register_new_player2(event, new_p, &e);
	pthread_mutex_unlock(&g_game->sychro_mutex);
	ft_strncpy(e->name, event->player_name, 19);
	e->name[19] = 0;
	e->is_rat = event->t;
	new_p->entity = e;
	new_p->i = i;
	ft_lstadd_back(&g_server.players, ft_lstnew(new_p));
	ft_lstadd_back(&g_data.multiplayer_entities, ft_lstnew(new_p->entity));
	printf("Added entity\n");
	g_data.player_count++;
}
