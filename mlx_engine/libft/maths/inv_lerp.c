/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inv_lerp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:50:02 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/18 07:01:17 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_maths.h"

inline float	ft_invlerp(float a, float b, float value)
{
	return ((value - a) / (b - a));
}

inline t_v2	ft_invlerp2(t_v2 a, t_v2 b, t_v2 t)
{
	return (v2((t.x - a.x) / (b.x - a.x),
			(t.y - a.y) / (b.y - a.y)));
}

inline t_v3	ft_invlerp3(t_v3 a, t_v3 b, t_v3 t)
{
	return (v3((t.x - a.x) / (b.x - a.x),
			(t.y - a.y) / (b.y - a.y),
			(t.z - a.z) / (b.z - a.z)));
}

inline t_v4	ft_invlerp4(t_v4 a, t_v4 b, t_v4 t)
{
	return (v4((t.x - a.x) / (b.x - a.x),
			(t.y - a.y) / (b.y - a.y),
			(t.z - a.z) / (b.z - a.z),
			(t.w - a.w) / (b.w - a.w)));
}
