/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_menu.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:10:27 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/27 13:46:53 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_MENU_H
# define OPTION_MENU_H

# include "cub3d.h"

extern t_ui		*g_root;
extern float	g_offset;

void	init_sensi_slider(void);
void	init_fov_slider(void);
void	init_return_button(void);
void	init_mouse_control_button(void);

#endif