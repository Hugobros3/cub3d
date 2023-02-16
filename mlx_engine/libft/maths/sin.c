/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 05:03:49 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/08 05:04:57 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_maths.h"

t_v2	ft_sin2(t_v2 v)
{
	return (v2(sin(v.x), sin(v.y)));
}

t_v3	ft_sin3(t_v3 v)
{
	return (v3(sin(v.x), sin(v.y), sin(v.z)));
}

t_v4	ft_sin4(t_v4 v)
{
	return (v4(sin(v.x), sin(v.y), sin(v.z), sin(v.w)));
}
