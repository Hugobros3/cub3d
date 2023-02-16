/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_sync.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 02:28:36 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/22 02:39:24 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_sync(t_xvar *xvar)
{
	int ret;

	pthread_mutex_lock(&(xvar->mutex));
	ret = XSync(xvar->display, False);
	pthread_mutex_unlock(&(xvar->mutex));
	return (ret);
}
