/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:47:36 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/08 04:44:14 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_maths.h"

inline float	ft_frac(float v)
{
	return (v - ((long)v));
}

inline t_v2	ft_frac2(t_v2 v)
{
	return (v2(ft_frac(v.x), ft_frac(v.y)));
}
