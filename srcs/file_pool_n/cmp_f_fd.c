/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_f_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 01:17:36 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 01:18:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "f_fd.h"

int	cmp_file_name(void *v1, void *v2)
{
	t_f_fd	*f1;
	char	*f2;

	f1 = (t_f_fd *)v1;
	f2 = (char *)v2;
	return (!ft_strcmp(f1->file, f2));
}

int	cmp_file_fd(void *v1, void *v2)
{
	t_f_fd	*f1;
	int		*f2;

	f1 = (t_f_fd *)v1;
	f2 = (int *)v2;
	return (!ft_memcmp(&f1->fd, f2, sizeof(int)));
}
