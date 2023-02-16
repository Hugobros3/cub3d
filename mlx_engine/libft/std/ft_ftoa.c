/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 00:01:59 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/24 15:53:02 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define AFTERPOINT 5

static void	reverse(char *str, int len)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	j = len - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

static int	int_to_str(int x, char str[], int d)
{
	int	i;

	i = 0;
	if (x == 0)
	{
		str[i] = '0';
		return (1);
	}
	while (x)
	{
		str[i++] = (x % 10) + '0';
		if (i >= (AFTERPOINT * 2 + 1))
		{
			str[i - 1] = '\0';
			return (-1);
		}
		x = x / 10;
	}
	while (i < d && i < (AFTERPOINT * 2 + 1) - 1)
		str[i++] = '0';
	reverse(str, i);
	str[i] = '\0';
	return (i);
}

char	*ft_ftoa(float n)
{
	int		ipart;
	float	fpart;
	int		i;
	char	*out;

	out = ft_malloc(sizeof(char) * (AFTERPOINT * 2 + 1));
	ft_bzero(out, sizeof(char) * (AFTERPOINT * 2 + 1));
	ipart = (int)n;
	fpart = n - (float)ipart;
	i = int_to_str(ipart, out, 0);
	if (i > 0 && i < (AFTERPOINT * 2 + 1) - 1)
	{
		out[i] = '.';
		fpart = fpart * pow(10, AFTERPOINT);
		int_to_str((int)fpart, out + i + 1, AFTERPOINT);
	}
	return (out);
}
