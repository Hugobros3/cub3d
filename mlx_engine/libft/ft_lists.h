/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:54:21 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/18 07:16:25 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LISTS_H
# define FT_LISTS_H

# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*prev;
	struct s_list	*next;
}				t_list;

//Compares every element in lst against ref using f, removes if f returns >0
int		ft_lstremoveif(t_list **lst, void (*del)(void *),
			int (*f)(), void *ref);

//Removes an element from a chained list. If del is not NULL,
//applies del to content and free the element
int		ft_lstremove(t_list **lst, t_list *elem, void (*del)(void *));

//Converts a list to an array
void	*ft_lst_to_array(t_list *lst, size_t elem_size);

//Creates and returns a new array containing
//all the pointers of the chained list
void	**ft_lst_to_array_pointers(t_list *lst);

//Creates a new list element using content
t_list	*ft_lstnew(void *content);

//Adds new at the front of lst.
void	ft_lstadd_front(t_list **lst, t_list *new);

//Returns the size of lst.
int		ft_lstsize(t_list *lst);

//Returns the last element of lst.
t_list	*ft_lstlast(t_list *lst);

//Adds new at the end of lst.
void	ft_lstadd_back(t_list **lst, t_list *new);

//Deletes an element from lst, using del on it's content.
void	ft_lstdelone(t_list *lst, void (*del)(void *));

//Iterates through lst, deleting every element (see ft_lstdelone).
void	ft_lstclear(t_list **lst, void (*del)(void *));

//Iterates through lst, using f on each element's content.
void	ft_lstiter(t_list *lst, void (*f)(void *));

t_list	*ft_lstfind(t_list *lst, int (*f)(), void *ref);

/*
Iterates through "lst", applies "f" on every
element's content, puts results in a new list and returns it.
"del" is used if anything goes wrong.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif