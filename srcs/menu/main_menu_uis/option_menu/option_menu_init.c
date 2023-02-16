/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_menu_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:11:11 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/27 13:47:17 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "option_menu.h"
#include "cub3d.h"

t_ui	*g_root;
float	g_offset;

void	init_option_menu(void)
{
	g_offset = 0.01;
	g_root = mlxe_create_ui(g_game->ui_root, "option menu root");
	g_root->block_del_on_clear = TRUE;
	init_sensi_slider();
	init_fov_slider();
	init_mouse_control_button();
	init_return_button();
	g_root->active = FALSE;
}
