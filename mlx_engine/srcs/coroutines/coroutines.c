/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coroutines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 11:53:37 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/27 14:21:27 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine_int.h"
#include "mlx_engine.h"

void	mlxe_start_coroutine(t_game *g, t_update_coroutine update,
	t_end_coroutine end, void *data)
{
	t_coroutine	*c;
	char		*name1;
	char		*name2;

	c = ft_malloc(sizeof(t_coroutine));
	c->data = data;
	c->update = update;
	c->on_end = end;
	ft_lstadd_back(&g->intern->coroutines, ft_lstnew(c));
	name1 = mlxe_get_symbol(update);
	name2 = mlxe_get_symbol(end);
	mlxe_log(GRN"Starting"RESET" coroutine '"YEL"%p"RESET"' (Update: '"
		YEL"%s"RESET"', End: '"YEL"%s"RESET"')\n",
		c, name1, name2);
	free(name1);
	free(name2);
}

void	mlxe_destroy_coroutine(t_game *g, t_coroutine *c)
{
	char	*name1;
	char	*name2;

	name1 = mlxe_get_symbol(c->update);
	name2 = mlxe_get_symbol(c->on_end);
	mlxe_log(RED"Removing"RESET" coroutine '"YEL"%p"RESET"' (Update: '"
		YEL"%s"RESET"', End: '"YEL"%s"RESET"')\n",
		c, name1, name2);
	ft_lstremoveif(&g->intern->coroutines, free, ft_cmpaddr, c);
	free(name1);
	free(name2);
}

void	mlxe_clear_coroutines(t_game *g)
{
	mlxe_log("Cleaning coroutines\n");
	ft_lstclear(&g->intern->coroutines, free);
}
