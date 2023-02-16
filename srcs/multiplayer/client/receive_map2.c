/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:05:43 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 19:23:54 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"
#include "raycast.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 8192

#ifdef LINUX

static int	create_temporary_file(char *path)
{
	int	fd;

	fd = open("/tmp", O_RDWR | __O_TMPFILE, S_IRUSR | S_IWUSR);
	if (fd < 0)
	{
		client_error("Invalid file path\n");
		return (-1);
	}
	if (add_file(path, fd) < 0)
	{
		fd = get_file_fd(path);
		close(fd);
	}
	return (fd);
}
#else

static int	create_temporary_file(char *path)
{
	char	*tmp_file;
	int		fd;

	tmp_file = ft_str_append(path, ".XXXX", 0, 0);
	fd = mkstemp(tmp_file);
	if (fd < 0)
	{
		client_error("Invalid file path\n");
		return (-1);
	}
	if (add_file(path, tmp_file, fd) < 0)
	{
		fd = get_file_fd(path);
		close(fd);
		unlink(tmp_file);
	}
	free(tmp_file);
	return (fd);
}
#endif

int	receive_file2(int s, int fd)
{
	int			file_size;
	long long	remain_data;
	int			len;
	char		buf[BUF_SIZE];

	file_size = 0;
	if (sync_read(s, &file_size, sizeof(long long)) < 0)
		return (client_error("Couldn't read file size"));
	client_log("File size received: %lld\n", file_size);
	remain_data = file_size;
	len = recv(s, buf, ft_minlong((long long)(sizeof(char) * BUF_SIZE),
				remain_data), 0);
	while (remain_data > 0 && len > 0)
	{
		if (len < 0 || sync_write(fd, buf, sizeof(char) * len) < 0)
			return (client_error("File read error"));
		remain_data -= len;
		len = recv(s, buf, ft_minlong((long long)(sizeof(char) * BUF_SIZE),
					remain_data), 0);
	}
	return (0);
}

int	receive_file(int s)
{
	char		*path;
	int			fd;

	if (read_path(s, &path) < 0)
		return (-1);
	fd = create_temporary_file(path);
	if (fd < 0)
	{
		free(path);
		return (-1);
	}
	free(path);
	receive_file2(s, fd);
	client_log("Done\n");
	return (0);
}

int	receive_all_files(int s)
{
	int		files_used_count;
	int		i;

	files_used_count = 0;
	if (sync_read(s, &files_used_count, sizeof(int)) < 0)
	{
		client_error("Couldn't read files used size");
		return (-1);
	}
	i = 0;
	while (i < files_used_count)
	{
		if (receive_file(s) < 0)
		{
			client_error("Couldn't read file");
			return (-1);
		}
		i++;
	}
	return (0);
}
