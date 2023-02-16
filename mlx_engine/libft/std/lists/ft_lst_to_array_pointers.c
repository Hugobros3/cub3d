/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_array_pointers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 07:06:20 by estarck           #+#    #+#             */
/*   Updated: 2023/01/18 07:06:25 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_lst_to_array_pointers(t_list *lst)
{
	int		lst_len;
	void	**out;
	t_list	*curr;
	int		i;

	lst_len = ft_lstsize(lst);
	out = ft_malloc(sizeof(void *) * (lst_len + 1));
	curr = lst;
	i = 0;
	while (curr)
	{
		out[i] = curr->content;
		curr = curr->next;
		i++;
	}
	out[i] = NULL;
	return (out);
}
