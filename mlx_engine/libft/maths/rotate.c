/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:56:39 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/06 22:57:03 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_maths.h"

t_v2	ft_rotate2(t_v2 v, float angle, t_v2 origin)
{
	t_v2	p;
	t_v2	tmp;

	p.x = v.x - origin.x;
	p.y = v.y - origin.y;
	tmp.x = p.x * cos(angle) - p.y * sin(angle);
	tmp.y = p.x * sin(angle) + p.y * cos(angle);
	return (v2(tmp.x + origin.x, tmp.y + origin.y));
}
