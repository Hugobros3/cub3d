/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 20:48:05 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 00:34:15 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine_int.h"
#include "mlx_engine.h"

#ifdef LINUX

void	mlxe_mouse_move(t_game *g, t_iv2 pos)
{
	mlx_mouse_move(g->mlx, g->window, pos.x, pos.y);
}
#elif OSX

void	mlxe_mouse_move(t_game *g, t_iv2 pos)
{
	mlx_mouse_move(g->window, pos.x, pos.y);
}
#endif