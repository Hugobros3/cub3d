/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 03:02:43 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/24 15:59:10 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine_int.h"
#include "mlx_engine.h"

#ifdef DEBUG

void	mlxe_log(char *msg, ...)
{
	va_list	l;

	va_start(l, msg);
	printf(MLXE_TAG);
	vprintf(msg, l);
}
#else

void	mlxe_log(char *msg, ...)
{
	(void)msg;
}
#endif
