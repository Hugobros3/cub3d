/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_menu_switch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:23:03 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/25 19:32:21 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "option_menu.h"
#include "cub3d.h"

void	switch_option_menu(void (*f)())
{
	g_root->active = !g_root->active;
	g_root->data = f;
}
