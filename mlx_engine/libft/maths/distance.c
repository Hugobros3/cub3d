/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:40:54 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/18 06:57:05 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_maths.h"

inline float	ft_dist2(t_v2 p1, t_v2 p2)
{
	return (sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2)));
}

inline float	ft_sqrdist2(t_v2 p1, t_v2 p2)
{
	return (powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2));
}

inline float	ft_dist3(t_v3 p1, t_v3 p2)
{
	return (sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2)
			+ powf(p1.y - p2.y, 2)));
}

inline float	ft_sqrdist3(t_v3 p1, t_v3 p2)
{
	return (powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2) + powf(p1.y - p2.y, 2));
}
