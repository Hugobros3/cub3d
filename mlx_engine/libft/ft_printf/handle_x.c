/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:28:55 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/17 00:24:00 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static void	add_to_char_buff(char *buf, char c)
{
	static int	i = 0;

	if (!buf)
	{
		i = 0;
		return ;
	}
	buf[i] = c;
	i++;
}

static void	convert(unsigned int num, char *out)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (num >= 16)
	{
		convert(num / 16, out);
		convert(num % 16, out);
	}
	else
		add_to_char_buff(out, hexa[num]);
}

int	handle_x(unsigned int i)
{
	char	out[8];
	int		ret;

	ft_bzero(out, sizeof(char) * 8);
	if (i == 0)
		add_to_char_buff(out, '0');
	else
		convert(i, out);
	ret = write(1, out, ft_strlen(out));
	add_to_char_buff(NULL, '0');
	return (ret);
}
