/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_fd.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 01:17:12 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 13:01:31 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef F_FD_H
# define F_FD_H

# include "cub3d.h"
# include <fcntl.h>

# ifdef LINUX

typedef struct s_f_fd
{
	char	*file;
	int		fd;
}	t_f_fd;
# else

typedef struct s_f_fd
{
	char	*file;
	char	*replace;
	int		fd;
}	t_f_fd;
# endif

int		cmp_file_name(void *v1, void *v2);
int		cmp_file_fd(void *v1, void *v2);
void	free_f_fd(void *v);
void	cleanup_file_pool(void);

#endif