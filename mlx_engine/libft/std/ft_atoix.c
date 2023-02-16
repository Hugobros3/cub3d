/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoix.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:21:01 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/18 07:13:04 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdint.h>

static int	add_to_char_buff(char *buf, char c, size_t size)
{
	static unsigned int	i = 0;

	if (!buf || i > size - 1)
	{
		i = 0;
		return (0);
	}
	buf[i] = c;
	i++;
	return (1);
}

int	convert(unsigned long num, char *out, size_t size)
{
	char	*hexa;
	int		ret;

	hexa = "0123456789abcdef";
	if (num >= 16)
	{
		ret = convert(num / 16, out, size);
		if (!ret)
			return (0);
		ret = convert(num % 16, out, size);
		if (!ret)
			return (0);
	}
	else
		return (add_to_char_buff(out, hexa[num], size));
	return (1);
}

void	ft_atoix(unsigned long i, char *buf, size_t size)
{
	ft_bzero(buf, size);
	if (i == 0)
		add_to_char_buff(buf, '0', size);
	else
		convert(i, buf, size);
	add_to_char_buff(NULL, '0', size);
}
