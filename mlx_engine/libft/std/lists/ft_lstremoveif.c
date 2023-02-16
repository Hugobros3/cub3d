/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremoveif.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 02:05:10 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/24 15:46:46 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lstremoveif2(t_list **lst, t_list *prev,
		t_list *curr, void (*del)(void *))
{
	if (prev == NULL)
		(*lst) = curr->next;
	else
	{
		prev->next = curr->next;
		if (ft_lstsize(prev) == 1)
			prev->next = NULL;
	}
	ft_lstdelone(curr, del);
	return (1);
}

int	ft_lstremoveif(t_list **lst, void (*del)(void *),
			int (*f)(), void *ref)
{
	t_list	*prev;
	t_list	*curr;

	if (!f || !lst || !(*lst))
		return (-1);
	curr = (*lst);
	prev = NULL;
	while (curr)
	{
		if (f(curr->content, ref))
			return (ft_lstremoveif2(lst, prev, curr, del));
		prev = curr;
		curr = curr->next;
	}
	return (0);
}
