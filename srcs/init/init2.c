/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:10:58 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 15:11:31 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycast.h"

static char	*debug_get_hostname(void *p)
{
	return (ft_strdup(p));
}

void	get_user_name(void)
{
	static char	*default_name = "My PC sucks";
	int			r;
	char		*tmp;
	time_t		t;

	t = time(NULL);
	ft_bzero(g_data.hostname, HOSTNAME_SIZE * sizeof(char));
	if (getlogin_r(g_data.hostname, HOSTNAME_SIZE) != 0)
		ft_strcpy(g_data.hostname, default_name);
	r = (int)(ft_frand((unsigned int)t) * 1000);
	tmp = ft_itoa(r);
	ft_strncpy(g_data.hostname + ft_strlen(g_data.hostname),
		tmp, sizeof(char) * 3);
	free(tmp);
	mlxdg_create_entry(g_game, "Hostname: ", debug_get_hostname,
		g_data.hostname);
}
