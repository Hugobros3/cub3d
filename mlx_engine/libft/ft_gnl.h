/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:09:34 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/18 06:38:15 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GNL_H
# define FT_GNL_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_save
{
	int				fd;
	char			*save;
}	t_save;

t_save	*gnl_lstnew(int fd);
t_list	*gnl_addback(t_list **lst, int fd);
void	gnl_lstfree(t_list **first, int fd);
char	*save_remaining(char	*save);
void	save_remaining2(t_list *s);
t_list	*get_save(t_list **save_list, int fd);

#endif
