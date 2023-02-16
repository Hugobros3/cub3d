/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_fd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:22:10 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 13:27:47 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "f_fd.h"

#ifdef LINUX

int	add_file(char *filename, int fd)
{
	t_f_fd	*f;
	t_list	*result;

	result = ft_lstfind(g_files_pool, cmp_file_name, filename);
	if (result)
		return (((t_f_fd *)result->content)->fd);
	f = ft_malloc(sizeof(t_f_fd));
	f->file = ft_strdup(filename);
	f->fd = fd;
	ft_lstadd_back(&g_files_pool, ft_lstnew(f));
	return (0);
}
#else

int	add_file(char *filename, char *tmp, int fd)
{
	t_f_fd	*f;
	t_list	*result;

	result = ft_lstfind(g_files_pool, cmp_file_name, filename);
	if (result)
		return (((t_f_fd *)result->content)->fd);
	f = ft_malloc(sizeof(t_f_fd));
	f->file = ft_strdup(filename);
	f->replace = ft_strdup(tmp);
	f->fd = fd;
	ft_lstadd_back(&g_files_pool, ft_lstnew(f));
	return (0);
}
#endif

int	get_file_fd(char *filename)
{
	t_list	*result;

	result = ft_lstfind(g_files_pool, cmp_file_name, filename);
	if (!result)
		return (-1);
	return (((t_f_fd *)result->content)->fd);
}

char	*get_file_name(int fd)
{
	t_list	*result;

	result = ft_lstfind(g_files_pool, cmp_file_fd, &fd);
	if (!result)
		return (NULL);
	return (((t_f_fd *)result->content)->file);
}

int	fp_open(char *filepath, int flags)
{
	int	fd;

	fd = get_file_fd(filepath);
	if (fd < 0)
		fd = open(filepath, flags);
	if (fd >= 0)
		lseek(fd, 0, SEEK_SET);
	return (fd);
}
