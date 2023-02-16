/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:54:04 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/31 17:22:17 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer.h"

void	free_sock(void *v)
{
	int	*s;

	s = (int *)v;
	close(*s);
	free(s);
}

void	free_mesh(t_mesh *m)
{
	free(m->triangles);
	clReleaseMemObject(m->tris_buffer);
	free(m);
}

void	free_entity(t_entity *e)
{
	free_mesh(e->m);
	clReleaseMemObject(e->tex_buf);
	free(e);
}

void	free_m_player(void *v)
{
	t_m_player	*p;

	p = (t_m_player *)v;
	remove_light(p->flashlight);
	free(p);
}

void	free_thread(void *v)
{
	pthread_t	*t;

	t = (pthread_t *)v;
	pthread_join(*t, NULL);
	free(t);
}
