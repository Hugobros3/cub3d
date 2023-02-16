/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_conversions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:03:26 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 20:04:16 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "events_builder.h"
#include <stdio.h>
#include <float.h>

char	*float_to_char(float f)
{
	char	*buf;
	int		size;

	size = FLT_DECIMAL_DIG + 9;
	buf = malloc(sizeof(char) * size);
	snprintf(buf, size, "%.*e", FLT_DECIMAL_DIG - 1, f);
	return (buf);
}

float	char_to_float(char *f)
{
	float	out;

	out = atof(f);
	return (out);
}
