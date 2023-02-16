/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:44:02 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/06 23:16:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_maths.h"

t_v3	ft_normalize3(t_v3 v)
{
	float	mag;

	mag = ft_dot3(v, v);
	if (mag > 0.00001)
		return (v3(sqrt(v.x / mag), sqrt(v.y / mag), sqrt(v.z / mag)));
	else
		return (v3(0.0, 0.0, 0.0));
}

t_v2	ft_normalize2(t_v2 v)
{
	float	length;
	t_v2	cpy;

	cpy = v;
	length = sqrtf(cpy.x * cpy.x + cpy.y * cpy.y);
	cpy.x /= length;
	cpy.y /= length;
	return (cpy);
}
