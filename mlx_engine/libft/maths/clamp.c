/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:37:50 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/06 22:40:41 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_maths.h"

float	ft_clampf(float min, float max, float v)
{
	if (v > max)
		return (max);
	if (v < min)
		return (min);
	return (v);
}

int	ft_clamp(int min, int max, int v)
{
	if (v > max)
		return (max);
	if (v < min)
		return (min);
	return (v);
}
