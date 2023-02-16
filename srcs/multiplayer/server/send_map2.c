/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:20:03 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 14:28:55 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"
#include <fcntl.h>

#ifdef LINUX
# include <sys/sendfile.h>
#endif

#include <sys/stat.h>

int	send_file_path(int s, char *path)
{
	size_t	size;

	size = ft_strlen(path) + 1;
	if (write(s, &size, sizeof(int)) < 0)
		return (-1);
	if (write(s, path, sizeof(char) * size) < 0)
		return (-1);
	return (0);
}

#ifdef OSX

int	send_file(int s, char *path)
{
	int			fd;
	struct stat	file_stat;
	long long	offset;

	fd = open(path, O_RDONLY);
	printf("Sending file: %s\n", path);
	if (fstat(fd, &file_stat) < 0)
		return (server_error("Couldn't stat file !"));
	if (send_file_path(s, path) < 0)
		return (server_error("Couldn't send file path !"));
	if (write(s, &file_stat.st_size, sizeof(long long)) < 0)
		return (server_error("Couldn't send file size !"));
	offset = 0;
	if (sendfile(fd, s, 0, &offset, NULL, 0) < 0)
		return (server_error("Couldn't send file !"));
	printf("Server sent %lld bytes from file's data\n", offset);
	close(fd);
	return (0);
}
#else

int	send_file(int s, char *path)
{
	int			fd;
	struct stat	file_stat;
	off_t		offset;

	fd = open(path, O_RDONLY);
	server_log("Sending file: %s\n", path);
	if (fstat(fd, &file_stat) < 0)
		return (server_error("Couldn't stat file !"));
	if (send_file_path(s, path) < 0)
		return (server_error("Couldn't send file path !"));
	if (write(s, &file_stat.st_size, sizeof(long long)) < 0)
		return (server_error("Couldn't send file size !"));
	offset = 0;
	server_log("Begin file transfer...\n");
	if (sendfile(s, fd, &offset, file_stat.st_size) < 0)
	{
		server_error("Couldn't send file !");
		return (-1);
	}
	server_log("Server sent %ld bytes from file's data\n", offset);
	close(fd);
	return (0);
}
#endif

int	send_all_files(t_client_instance *i)
{
	t_list	*curr;
	int		size;

	curr = g_map.files_used;
	size = ft_lstsize(curr);
	server_log("Sending files used size...");
	if (write(i->s, &size, sizeof(int)) < 0)
	{
		server_error("\nCouldn't send files used size !");
		return (-1);
	}
	server_log("done !\n");
	while (curr)
	{
		if (send_file(i->s, curr->content) < 0)
		{
			server_error("Couldn't send file !");
			return (-1);
		}
		curr = curr->next;
	}
	server_log("Sent all files\n");
	return (0);
}
