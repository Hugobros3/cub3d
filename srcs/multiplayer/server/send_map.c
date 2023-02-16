/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:20:03 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:38:52 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"
#include <fcntl.h>

#ifdef LINUX
# include <sys/sendfile.h>
#endif

#include <sys/stat.h>

int	send_map(t_client_instance *instance)
{
	int		n;
	int		i;
	int		len;

	if (send_all_files(instance) < 0)
		return (server_error("Couldn't send all files\n"));
	i = 0;
	len = ft_splitlen(g_map.str);
	n = write(instance->s, &len, sizeof(int));
	if (n < 0)
		return (server_error("Couldn't send map split size !"));
	while (g_map.str[i])
	{
		len = ft_strlen(g_map.str[i]) + 1;
		n = write(instance->s, &len, sizeof(int));
		if (n < 0)
			return (server_error("Couldn't send line size !"));
		n = write(instance->s, g_map.str[i], len * sizeof(char));
		if (n < 0)
			return (server_error("Couldn't send line !"));
		i++;
	}
	return (0);
}
