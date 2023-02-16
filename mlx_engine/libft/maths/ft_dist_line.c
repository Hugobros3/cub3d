/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dist_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 04:34:41 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/24 15:55:08 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_maths.h"

float	ft_dist_line(t_v2 p, t_v2 s1, t_v2 s2)
{
	t_v2	ab;
	t_v2	cd;
	float	param;
	t_v2	d;
	t_v2	tmp;

	ab = sub2(p, s1);
	cd = sub2(s2, s1);
	param = -1;
	if (ft_dot2(cd, cd) != 0)
		param = ft_dot2(ab, cd) / ft_dot2(cd, cd);
	if (param < 0)
		tmp = v2(s1.x, s1.y);
	else if (param > 1)
		tmp = v2(s2.x, s2.y);
	else
		tmp = v2(s1.x + param * cd.x, s1.y + param * cd.y);
	d = sub2(p, tmp);
	return (sqrt(d.x * d.x + d.y * d.y));
}
