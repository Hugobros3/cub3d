/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_menu_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 23:10:31 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/25 19:31:19 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "escape_menu.h"

void	escape_menu_init(void)
{
	g_esc_menu.block_return = FALSE;
	escape_menu_root();
	escape_menu_continue();
	escape_menu_options();
	escape_menu_main_menu();
}
