/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:13:39 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 12:57:38 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include "mlx_engine.h"

typedef struct s_menu
{
	t_ui	*menu_root;
	t_ui	*start;
	t_ui	*options;
	t_ui	*quit;
}	t_menu;

void	menu_background_loop(t_game *g);
void	multiplayer_button(void);
void	start_button(void);
void	options_button(void);
void	quit_button(void);
void	mult_button(void);

void	lock_buttons(void);

void	find_place(void);

void	toggle_multiplayer_menu(void);
void	init_multiplayer_menu(void);

void	init_option_menu(void);

void	switch_mult_menu(void (*f)());
void	init_mult_menu(void);

extern t_menu	g_menu;

#endif