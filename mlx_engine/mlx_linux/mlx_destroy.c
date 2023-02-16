/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 02:27:15 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/22 02:36:57 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

void	mlx_destroy(void *mlx)
{
	t_xvar	*xvar;

	xvar = (t_xvar *)mlx;
	pthread_mutex_destroy(&(xvar->mutex));
}
