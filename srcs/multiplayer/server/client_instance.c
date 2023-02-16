/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_instance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:11:19 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/31 17:22:31 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"

#define ERR "\x1B[31mError: \x1B[0m"
#define ERR1 "Couldn't create client instance send thread !"
#define ERR2 "Couldn't create client instance receive thread !"

int	cmp_mplayer(void *v1, void *v2)
{
	t_m_player			*p;
	t_client_instance	*i;

	p = v1;
	i = v2;
	return (p->i == i);
}

static void	*client_instance_err(void *data, char *msg)
{
	free(data);
	server_log(msg);
	return (NULL);
}

void	remove_client_instance(t_client_instance *i)
{
	t_m_player	*p;
	t_list		*result;

	result = ft_lstfind(g_server.players, cmp_mplayer, i);
	if (result)
	{
		pthread_mutex_lock(&g_game->sychro_mutex);
		printf("REMOVING PLAYER\n");
		p = result->content;
		ft_lstremoveif(&g_data.multiplayer_entities,
			NULL, ft_cmpaddr, p->entity);
		printf("%p\n", g_data.multiplayer_entities);
		ft_lstremoveif(&g_server.players, free_m_player, ft_cmpaddr, p);
		g_server.player_count--;
		pthread_mutex_unlock(&g_game->sychro_mutex);
	}
}

void	*client_instance_thread(void *data)
{
	t_client_instance	*i;
	pthread_t			send_thread;
	pthread_t			receive_thread;

	i = (t_client_instance *)data;
	i->run = TRUE;
	server_log("Creating client instance...\n");
	if (send_map(i) < 0)
		return (client_instance_err(data, ERR"Couldn't send map"));
	if (pthread_create(&send_thread, NULL,
			client_instance_send_thread, data) != 0)
		return (client_instance_err(data, ERR ERR1));
	server_log("Created client instance send thread\n");
	if (pthread_create(&receive_thread, NULL,
			client_instance_receive_thread, data) != 0)
		return (client_instance_err(data, ERR ERR2));
	server_log("Created client instance receive thread\n");
	pthread_join(send_thread, NULL);
	pthread_join(receive_thread, NULL);
	remove_client_instance(i);
	free(data);
	return (NULL);
}
