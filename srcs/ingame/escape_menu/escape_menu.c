/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 03:10:15 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/25 19:31:46 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "escape_menu.h"

t_escape_menu	g_esc_menu;

void	switch_escape_menu(void)
{
	static t_bool	shown = FALSE;

	if (g_esc_menu.block_return)
		return ;
	if (shown)
		hide_escape_menu();
	else
		show_escape_menu();
	shown = !shown;
}

void	show_escape_menu(void)
{
	g_esc_menu.root->active = TRUE;
	g_game->timescale = 0;
	g_settings.mouse_lock = FALSE;
}

void	hide_escape_menu(void)
{
	g_esc_menu.root->active = FALSE;
	g_game->timescale = 1;
	g_settings.mouse_lock = TRUE;
}
