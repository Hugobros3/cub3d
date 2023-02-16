/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_log.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:06:03 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/29 16:41:26 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"
#include <stdarg.h>

int	client_error(char *msg)
{
	printf(MAG"[Client] "RED"Error:"RESET);
	fflush(stdout);
	perror(msg);
	request_multi_stop();
	return (-1);
}

void	client_log(char *msg, ...)
{
	va_list	l;

	va_start(l, msg);
	printf(MAG"[Client] "RESET);
	vprintf(msg, l);
	va_end(l);
}
