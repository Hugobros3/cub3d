/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:43:10 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 01:02:50 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine_int.h"
#include "mlx_engine.h"

void	exec_loop_hooks(t_game *g)
{
	t_list	*curr;
	t_list	*next;

	curr = g->intern->loop_hooks;
	while (curr)
	{
		next = curr->next;
		((t_loop_hook)curr->content)(g);
		curr = next;
	}
}

#ifndef DEBUG

void	mlxe_remove_loop_hook(t_game *g, t_loop_hook hook)
{
	mlxe_log(RED"Removed"RESET" loop hook: "YEL"%p"RESET"\n", hook);
	ft_lstremoveif(&g->intern->loop_hooks, NULL, ft_cmpaddr, hook);
}

static void	print_removed_hook(void *p)
{
	mlxe_log(RED"Removed"RESET" loop hook: "YEL"%p"RESET"\n", p);
}

void	mlxe_clear_loop_hooks(t_game *g)
{
	mlxe_log("Clearing loop hook...\n");
	ft_lstclear(&g->intern->loop_hooks, print_removed_hook);
}

void	mlxe_add_loop_hook(t_game *g, t_loop_hook hook)
{
	mlxe_log(GRN"Added"RESET" loop hook: "YEL"%p"RESET"\n", hook);
	ft_lstadd_back(&g->intern->loop_hooks, ft_lstnew(hook));
}
#endif