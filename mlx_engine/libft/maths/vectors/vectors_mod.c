/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors14.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:41:09 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/12 22:43:03 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"

t_iv2	mod2i(t_iv2 v1, t_iv2 v2)
{
	return (iv2(v1.x % v2.x, v1.y % v2.y));
}

t_iv3	mod3i(t_iv3 v1, t_iv3 v2)
{
	return (iv3(v1.x % v2.x, v1.y % v2.y, v1.z % v2.z));
}

t_iv4	mod4i(t_iv4 v1, t_iv4 v2)
{
	return (iv4(v1.x % v2.x, v1.y % v2.y, v1.z % v2.z, v1.w % v2.w));
}
