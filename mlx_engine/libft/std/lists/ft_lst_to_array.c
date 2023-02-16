/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 01:21:21 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/21 19:09:20 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lst_to_array(t_list *lst, size_t elem_size)
{
	int		lst_len;
	void	*out;
	t_list	*curr;
	int		i;

	if (!lst)
		return (NULL);
	lst_len = ft_lstsize(lst);
	out = ft_malloc(elem_size * lst_len);
	curr = lst;
	i = 0;
	while (curr)
	{
		ft_memcpy(out + (i * elem_size), curr->content, elem_size);
		curr = curr->next;
		i++;
	}
	return (out);
}
