/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_i_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:34:29 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/18 06:53:35 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include <stdlib.h>

inline t_v4	v4_inv_lerp(t_v4 a, t_v4 b, t_v4 t)
{
	return (v4((t.x - a.x) / (b.x - a.x), (t.y - a.y) / (b.y - a.y),
			(t.z - a.z) / (b.z - a.z), (t.w - a.w) / (b.w - a.w)));
}

inline t_iv2	add2i(t_iv2 a, t_iv2 b)
{
	return (iv2(a.x + b.x, a.y + b.y));
}

inline t_iv3	add3i(t_iv3 a, t_iv3 b)
{
	return (iv3(a.x + b.x, a.y + b.y, a.z + b.z));
}

inline t_iv4	add4i(t_iv4 a, t_iv4 b)
{
	return (iv4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w));
}
