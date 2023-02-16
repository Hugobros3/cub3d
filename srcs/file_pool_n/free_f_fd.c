/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_f_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 01:16:43 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 01:20:51 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "f_fd.h"

#ifdef LINUX

void	free_f_fd(void *v)
{
	t_f_fd	*f;

	f = (t_f_fd *)v;
	free(f->file);
	close(f->fd);
	free(f);
}
#else

void	free_f_fd(void *v)
{
	t_f_fd	*f;

	f = (t_f_fd *)v;
	close(f->fd);
	unlink(f->replace);
	free(f->file);
	free(f->replace);
	free(f);
}
#endif

void	cleanup_file_pool(void)
{
	ft_lstclear(&g_files_pool, free_f_fd);
}
