/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_ui.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 23:45:27 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/25 23:46:27 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXE_UI_H
# define MLXE_UI_H

# include "mlx_engine_int.h"
# include "mlx_engine.h"

void	select_ui(t_game *g, t_ui *ui);
void	unselect_ui(t_game *g);

#endif