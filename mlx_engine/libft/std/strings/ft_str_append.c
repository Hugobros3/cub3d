/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:24:52 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/18 07:10:37 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_append(char *a, char *b, int free_a, int free_b)
{
	char	*new;

	new = ft_strjoin(a, b);
	if (free_a)
		free(a);
	if (free_b)
		free(b);
	return (new);
}
