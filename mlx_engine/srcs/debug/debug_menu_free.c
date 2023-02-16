/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_menu_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:42:59 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 15:22:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_menu.h"

void	mlxdg_free_debug_menu(t_game *g)
{
	if (!g->intern->debug_m.init)
		return ;
	ft_lstclear(&g->intern->debug_m.entries,
		(void (*)(void *))free_debug_entry);
	mlxe_free_font(g->intern->debug_m.font);
	g->intern->debug_m.init = FALSE;
}
