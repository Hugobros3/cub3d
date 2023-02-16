/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:44:30 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/18 06:52:58 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"

inline t_v2	v2(float x, float y)
{
	return ((t_v2){.x = x, .y = y});
}

inline t_v3	v3(float x, float y, float z)
{
	return ((t_v3){.x = x, .y = y, .z = z});
}

inline t_v4	v4(float x, float y, float z, float w)
{
	return ((t_v4){.x = x, .y = y, .z = z, .w = w});
}
