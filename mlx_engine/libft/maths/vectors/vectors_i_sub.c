/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_i_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:34:29 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/12 22:46:37 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include <stdlib.h>

inline t_iv2	sub2i(t_iv2 a, t_iv2 b)
{
	return (iv2(a.x - b.x, a.y - b.y));
}

inline t_iv3	sub3i(t_iv3 a, t_iv3 b)
{
	return (iv3(a.x - b.x, a.y - b.y, a.z - b.z));
}

inline t_iv4	sub4i(t_iv4 a, t_iv4 b)
{
	return (iv4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w));
}
