/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_log.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:07:16 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/29 16:41:30 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../multiplayer.h"
#include <stdarg.h>

int	server_error(char *msg)
{
	printf(MAG"[Server] "RED"Error:"RESET);
	perror(msg);
	request_multi_stop();
	return (-1);
}

void	server_log(char *msg, ...)
{
	va_list	l;

	va_start(l, msg);
	printf(MAG"[Server] "RESET);
	vprintf(msg, l);
	va_end(l);
}
