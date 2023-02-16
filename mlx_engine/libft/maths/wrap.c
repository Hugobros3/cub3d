/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:54:03 by reclaire          #+#    #+#             */
/*   Updated: 2022/06/08 15:54:03 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_maths.h"

int	ft_wrap(int n, int min, int max)
{
	int	range;

	range = max - min + 1;
	n = ((n - min) % range);
	if (n < 0)
		return (max + 1 + n);
	else
		return (min + n);
}

float	ft_fwrap(float x, float min, float max)
{
	float	f;

	if (x >= 0)
		f = min;
	else
		f = max;
	return (f + fmod(x, max - min));
}
