/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_menu_root.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 03:05:32 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 15:44:05 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "escape_menu.h"

void	escape_menu_root(void)
{
	t_ui	*root;

	root = mlxe_create_ui(g_game->ui_root, "escape menu root");
	root->pos = v2(0, 0);
	root->size = v2(1, 1);
	root->active = FALSE;
	root->eval = mlxcl_create_ui_program(g_game,
			"./srcs/ingame/escape_menu/root_eval.cl", "-I./include");
	g_esc_menu.root = root;
}
