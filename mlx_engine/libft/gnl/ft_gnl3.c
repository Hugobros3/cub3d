/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 06:36:17 by estarck           #+#    #+#             */
/*   Updated: 2023/01/18 06:40:18 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_gnl.h"

#define BUFFER_SIZE 1

t_list	*get_save(t_list **save_list, int fd)
{
	t_list	*current;

	if (!(*save_list))
	{
		(*save_list) = ft_malloc(sizeof(t_list));
		(*save_list)->content = gnl_lstnew(fd);
		(*save_list)->next = NULL;
	}
	current = *save_list;
	while (current)
	{
		if (((t_save *)(current->content))->fd == fd)
			break ;
		current = current->next;
	}
	if (!current)
		current = gnl_addback(save_list, fd);
	return (current);
}
