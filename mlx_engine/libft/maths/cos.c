/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 05:05:05 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/08 05:05:20 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_maths.h"

t_v2	ft_cos2(t_v2 v)
{
	return (v2(cos(v.x), cos(v.y)));
}

t_v3	ft_cos3(t_v3 v)
{
	return (v3(cos(v.x), cos(v.y), cos(v.z)));
}

t_v4	ft_cos4(t_v4 v)
{
	return (v4(cos(v.x), cos(v.y), cos(v.z), cos(v.w)));
}
