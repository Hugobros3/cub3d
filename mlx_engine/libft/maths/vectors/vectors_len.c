/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors11.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:34:29 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/12 22:44:21 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include <stdlib.h>

inline int	vlen2i(t_iv2 a)
{
	return (a.x * a.y);
}

inline float	vlen2(t_v2 a)
{
	return (a.x * a.y);
}
