/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_noise2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 05:03:12 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/24 15:54:19 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_maths.h"

float	ft_noise2(t_v2 st)
{
	t_v2	i;
	t_v2	f;
	t_v4	abcd;
	t_v2	u;

	f = ft_frac2(st);
	i = v2(floorf(st.x), floorf(st.y));
	abcd.x = ft_frand2(i);
	abcd.y = ft_frand2(add2(i, v2(1.0, 0.0)));
	abcd.z = ft_frand2(add2(i, v2(0.0, 1.0)));
	abcd.w = ft_frand2(add2(i, v2(1.0, 1.0)));
	u = ft_smoothstep2(v2(0, 0), v2(1, 1), f);
	return (ft_lerp(abcd.x, abcd.y, u.x) + (abcd.z - abcd.x) * u.y * (1.0 - u.x)
		+ (abcd.w - abcd.y) * u.x * u.y);
}
