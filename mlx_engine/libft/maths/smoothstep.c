/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smoothstep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 21:38:10 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/08 21:38:21 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_maths.h"

inline float	ft_smoothstep(float x, float y, float s)
{
	return (ft_lerp(x, y, s * s * (3 - 2 * s)));
}

inline t_v2	ft_smoothstep2(t_v2 x, t_v2 y, t_v2 s)
{
	return (v2(ft_smoothstep(x.x, y.x, s.x), ft_smoothstep(x.y, y.y, s.y)));
}
