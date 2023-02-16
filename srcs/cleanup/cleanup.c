/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:30:27 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/28 22:24:35 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cleanup.h"

void	cleanup(void)
{
	stop_multiplayer();
	mlxdg_free_debug_menu(g_game);
	cleanup_map(&g_map);
	ft_lstclear(&g_data.entities, (void (*)(void *))cleanup_entity);
	raycast_cleanup();
	mlxe_free_game(g_game);
}

void	quit_cub3d(void)
{
	cleanup();
	exit(0);
}
