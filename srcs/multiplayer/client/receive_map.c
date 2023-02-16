/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:28:39 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 18:36:39 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"
#include "raycast.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 8192

long long	ft_minlong(long long v1, long long v2)
{
	if (v1 < v2)
		return (v1);
	else
		return (v2);
}

int	read_path(int s, char **path)
{
	int			path_size;

	path_size = 0;
	if (sync_read(s, &path_size, sizeof(int)) < 0)
	{
		client_error("Couldn't read path size");
		return (-1);
	}
	client_log("Path size received: %d\n", path_size);
	*path = ft_malloc(sizeof(char) * path_size);
	if (sync_read(s, *path, sizeof(char) * path_size) < 0)
	{
		client_error("Couldn't read path");
		free(*path);
		return (-1);
	}
	client_log("File path received: %.*s\n", 40, path);
	return (0);
}

static char	**error_return(char *msg)
{
	client_error(msg);
	return (NULL);
}

static char	**receive_map3(int s)
{
	char	**new_str;
	int		len;
	int		len2;
	int		i;

	if (sync_read(s, &len, sizeof(int)) < 0)
		return (error_return("Couldn't read map split size"));
	i = 0;
	new_str = ft_malloc(sizeof(char *) * (len + 1));
	ft_bzero(new_str, sizeof(char *) * (len + 1));
	while (i < len)
	{
		if (sync_read(s, &len2, sizeof(int)) < 0)
			return (ft_freesplit(new_str),
				error_return("Couldn't read map line size"));
		new_str[i] = ft_malloc(sizeof(char) * len2);
		if (sync_read(s, new_str[i], sizeof(char) * len2) < 0)
			return (ft_freesplit(new_str),
				error_return("Couldn't read map line"));
		i++;
	}
	new_str[i] = NULL;
	return (new_str);
}

int	receive_map(int s)
{
	char	**new_str;

	receive_all_files(s);
	new_str = receive_map3(s);
	if (!new_str)
		return (-1);
	pthread_mutex_lock(&g_raycast.map_buffer_m);
	parse_map(new_str);
	clReleaseMemObject(g_raycast.map_buffer);
	g_raycast.map_buffer = mlxcl_create_buffer(g_game->cl_data, CL_RD,
			sizeof(int) * vlen2i(g_map.size), g_map.data);
	cleanup_file_pool();
	ft_lstclear(&g_data.lights, free);
	copy_map_lights();
	raycast_init();
	init_renderer();
	pthread_mutex_unlock(&g_raycast.map_buffer_m);
	return (0);
}
