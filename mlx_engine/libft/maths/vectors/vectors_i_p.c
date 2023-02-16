/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_i_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:34:29 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/12 22:55:18 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include <stdlib.h>

t_iv2	*piv2(int x, int y)
{
	t_iv2	*p;

	p = malloc(sizeof(t_iv2));
	p->x = x;
	p->y = y;
	return (p);
}

t_iv3	*piv3(int x, int y, int z)
{
	t_iv3	*p;

	p = malloc(sizeof(t_iv3));
	p->x = x;
	p->y = y;
	p->z = z;
	return (p);
}

t_iv4	*piv4(int x, int y, int z, int w)
{
	t_iv4	*p;

	p = malloc(sizeof(t_iv4));
	p->x = x;
	p->y = y;
	p->z = z;
	p->w = w;
	return (p);
}
