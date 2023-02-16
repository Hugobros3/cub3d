/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:43:10 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 01:03:01 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine_int.h"
#include "mlx_engine.h"
#ifdef DEBUG
# include <dlfcn.h>

void	mlxe_remove_loop_hook(t_game *g, t_loop_hook hook)
{
	Dl_info	info;

	dladdr(hook, &info);
	mlxe_log(RED"Removed"RESET" loop hook: "YEL"%s"RESET"\n", info.dli_sname);
	ft_lstremoveif(&g->intern->loop_hooks, NULL, ft_cmpaddr, hook);
}

static void	print_removed_hook(void *p)
{
	Dl_info	info;

	dladdr(p, &info);
	mlxe_log(RED"Removed"RESET" loop hook: "YEL"%s"RESET"\n", info.dli_sname);
}

void	mlxe_clear_loop_hooks(t_game *g)
{
	mlxe_log("Clearing loop hook...\n");
	ft_lstclear(&g->intern->loop_hooks, print_removed_hook);
}

void	mlxe_add_loop_hook(t_game *g, t_loop_hook hook)
{
	Dl_info	info;

	dladdr(hook, &info);
	mlxe_log(GRN"Added"RESET" loop hook: "YEL"%s"RESET"\n", info.dli_sname);
	ft_lstadd_back(&g->intern->loop_hooks, ft_lstnew(hook));
}
#endif
