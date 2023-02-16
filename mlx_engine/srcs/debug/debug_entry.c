/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:20:42 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 15:23:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_menu.h"

void	free_debug_entry(t_debug_entry *e)
{
	free(e->name);
	free(e);
}

void	mlxdg_create_entry(t_game *g, char *name,
	char *(*get)(void *), void *data)
{
	t_debug_entry	*e;

	e = ft_malloc(sizeof(t_debug_entry));
	e->name = ft_strdup(name);
	e->data = data;
	e->get = get;
	ft_lstadd_back(&g->intern->debug_m.entries, ft_lstnew(e));
	g->intern->debug_m.index++;
}

static int	cmp_entry(void *d1, void *d2)
{
	char			*ref;
	t_debug_entry	*e;

	e = (t_debug_entry *)d1;
	ref = (char *)d2;
	return (!ft_strcmp(e->name, ref));
}

void	mlxdg_remove_entry(t_game *g, char *name)
{
	ft_lstremoveif(&g->intern->debug_m.entries,
		(void (*)(void *))free_debug_entry, cmp_entry, name);
}
