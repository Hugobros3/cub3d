/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_menu.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 23:11:14 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 15:45:18 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ESCAPE_MENU_H
# define ESCAPE_MENU_H

# include "cub3d.h"

typedef struct s_escape_menu
{
	t_ui	*root;
	t_ui	*continue_button;
	t_ui	*options_button;
	t_ui	*main_menu_button;
	t_bool	block_return;
}	t_escape_menu;

extern t_escape_menu	g_esc_menu;

void	escape_menu_root(void);
void	escape_menu_continue(void);
void	escape_menu_options(void);
void	escape_menu_main_menu(void);

#endif