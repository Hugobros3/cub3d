/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_menu_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:56:05 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/29 19:30:21 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mult_menu.h"

t_ui	*g_mult_root;

void	init_mult_menu(void)
{
	g_mult_root = mlxe_create_ui(g_game->ui_root, "mult menu root");
	init_host_button();
	init_mult_return_button();
	init_list_button();
	g_mult_root->active = FALSE;
}
