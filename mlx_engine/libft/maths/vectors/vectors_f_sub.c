/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_f_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:45:52 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/12 22:48:02 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"

inline t_v2	sub2(t_v2 a, t_v2 b)
{
	return (v2(a.x - b.x, a.y - b.y));
}

inline t_v3	sub3(t_v3 a, t_v3 b)
{
	return (v3(a.x - b.x, a.y - b.y, a.z - b.z));
}

inline t_v4	sub4(t_v4 a, t_v4 b)
{
	return (v4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w));
}
