/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_free2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:55:02 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 14:55:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer.h"

void	free_thread_force(void *v)
{
	pthread_t	*t;

	t = (pthread_t *)v;
	pthread_cancel(*t);
	pthread_join(*t, NULL);
	free(t);
}
