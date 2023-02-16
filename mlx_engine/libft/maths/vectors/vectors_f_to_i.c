/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors13.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 22:07:14 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/09 14:30:06 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"

inline t_iv2	v2iv2(t_v2 v)
{
	return (iv2(v.x, v.y));
}

inline t_iv3	v3iv3(t_v3 v)
{
	return (iv3(v.x, v.y, v.z));
}

inline t_iv4	v4iv4(t_v4 v)
{
	return (iv4(v.x, v.y, v.z, v.w));
}
