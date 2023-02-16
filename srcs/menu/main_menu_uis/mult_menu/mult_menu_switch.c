/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_menu_switch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:23:03 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/29 19:04:35 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mult_menu.h"
#include "../../menu.h"

void	switch_mult_menu(void (*f)())
{
	g_mult_root->active = !g_mult_root->active;
	g_mult_root->data = f;
}
