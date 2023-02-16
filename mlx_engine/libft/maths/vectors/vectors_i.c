/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:54:06 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/12 22:54:10 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"

inline t_iv2	iv2(int x, int y)
{
	return ((t_iv2){.x = x, .y = y});
}

inline t_iv3	iv3(int x, int y, int z)
{
	return ((t_iv3){.x = x, .y = y, .z = z});
}

inline t_iv4	iv4(int x, int y, int z, int w)
{
	return ((t_iv4){.x = x, .y = y, .z = z, .w = w});
}
