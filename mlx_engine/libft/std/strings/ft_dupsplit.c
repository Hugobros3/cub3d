/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dupsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:12:18 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/24 14:22:17 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dupsplit(char **s)
{
	int		size;
	int		i;
	char	**out;

	i = 0;
	size = ft_splitlen(s);
	out = ft_malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		out[i] = ft_strdup(s[i]);
		i++;
	}
	out[i] = NULL;
	return (out);
}
