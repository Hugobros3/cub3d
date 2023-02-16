/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:29:36 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/12 22:50:13 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_maths.h"

inline float	ft_lerp(float x, float y, float s)
{
	return (x + ft_clampf(0, 1, s) * (y - x));
}

inline t_v2	ft_lerp2(t_v2 v_1, t_v2 v_2, float t)
{
	return (v2(
			ft_lerp(v_1.x, v_2.x, t),
			ft_lerp(v_1.y, v_2.y, t)));
}

inline t_v3	ft_lerp3(t_v3 v_1, t_v3 v_2, float t)
{
	return (v3(
			ft_lerp(v_1.x, v_2.x, t),
			ft_lerp(v_1.y, v_2.y, t),
			ft_lerp(v_1.z, v_2.z, t)));
}

inline t_v4	ft_lerp4(t_v4 v_1, t_v4 v_2, float t)
{
	return (v4(
			ft_lerp(v_1.x, v_2.x, t),
			ft_lerp(v_1.y, v_2.y, t),
			ft_lerp(v_1.z, v_2.z, t),
			ft_lerp(v_1.w, v_2.w, t)));
}
