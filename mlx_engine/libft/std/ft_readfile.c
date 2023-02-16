/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:55:52 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/24 15:50:59 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gnl.h"

static int	ft_readfile2(int fd, int read_size, char **out)
{
	char	*buffer;
	char	*tmp;
	int		bytes_read;

	buffer = ft_malloc((read_size + 1) * sizeof(char));
	bytes_read = read(fd, buffer, read_size);
	if (bytes_read < 0)
	{
		free(buffer);
		return (bytes_read);
	}
	buffer[bytes_read] = '\0';
	tmp = *out;
	*out = ft_strjoin(tmp, buffer);
	free(tmp);
	free(buffer);
	return (bytes_read);
}

char	*ft_readfile(int fd, int read_size)
{
	t_list	*ret;
	char	*out;
	int		bytes_read;

	ret = ft_lstfind((t_list *)ft_gnl(-100), ft_cmpint, &fd);
	if (ret)
		out = ft_strdup(((t_save *)ret->content)->save);
	else
	{
		out = ft_malloc(sizeof(char));
		out[0] = '\0';
	}
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = ft_readfile2(fd, read_size, &out);
		if (bytes_read < 0)
			return (NULL);
	}
	ft_gnl(fd);
	return (out);
}
