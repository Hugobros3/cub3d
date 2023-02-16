/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_menu.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:54:44 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/29 19:30:09 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULT_MENU_H
# define MULT_MENU_H

# include "cub3d.h"

extern t_ui	*g_mult_root;

void	init_host_button(void);
void	init_mult_return_button(void);
void	init_list_button(void);

#endif