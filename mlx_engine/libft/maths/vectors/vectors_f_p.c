/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_f_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:47:19 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/12 22:55:16 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include <stdlib.h>

t_v2	*pv2(float x, float y)
{
	t_v2	*p;

	p = malloc(sizeof(t_v2));
	p->x = x;
	p->y = y;
	return (p);
}

t_v3	*pv3(float x, float y, float z)
{
	t_v3	*p;

	p = malloc(sizeof(t_v3));
	p->x = x;
	p->y = y;
	p->z = z;
	return (p);
}

t_v4	*pv4(float x, float y, float z, float w)
{
	t_v4	*p;

	p = malloc(sizeof(t_v4));
	p->x = x;
	p->y = y;
	p->z = z;
	p->w = w;
	return (p);
}
