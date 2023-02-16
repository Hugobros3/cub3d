/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_menu_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:21:25 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 00:21:55 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_menu.h"

void	init_debug_menu(t_game *g)
{
	if (g->intern->debug_m.init)
		return ;
	g->intern->debug_m.font = mlxe_init_font(g,
			"./mlx_engine/debug_font.ttf", iv2(16, 16));
	g->intern->debug_m.entries = NULL;
	g->intern->debug_m.index = 0;
	g->intern->debug_m.init = TRUE;
	g->intern->debug_m.graph = mlxcl_create_ui_program(g,
			"./mlx_engine/srcs/debug/debug_graph.cl", "");
	g->intern->debug_m.graph_data = mlxcl_create_buffer(g->cl_data,
			CL_RD, sizeof(float) * FPS_COUNTER_MAX, NULL);
}
