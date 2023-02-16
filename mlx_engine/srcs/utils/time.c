/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 03:03:18 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/24 15:58:49 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine_int.h"
#include "mlx_engine.h"

suseconds_t	mlxe_timestamp(void)
{
	struct timeval	te;

	gettimeofday(&te, NULL);
	return (te.tv_usec);
}

void	update_time(t_game *g)
{
	struct timeval		tv;
	unsigned long long	ms;

	gettimeofday(&tv, NULL);
	ms = (unsigned long long)(tv.tv_sec) *1000
		+ (unsigned long long)(tv.tv_usec) / 1000;
	g->unscaled_d_time = (ms - g->last_time) / 1000.0;
	g->last_time = ms;
	g->d_time = g->unscaled_d_time * g->timescale;
	g->time += g->unscaled_d_time;
}
