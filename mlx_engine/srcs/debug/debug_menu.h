/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_menu.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:19:10 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 00:23:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_MENU_H
# define DEBUG_MENU_H

# include "mlx_engine_int.h"
# include "mlx_engine.h"
# include <float.h>

typedef struct s_debug_entry
{
	char	*name;
	char	*(*get)(void *);
	void	*data;
}	t_debug_entry;

void	free_debug_entry(t_debug_entry *e);
void	init_debug_menu(t_game *g);
void	mlxdg_create_entry(t_game *g, char *name,
			char *(*get)(void *), void *data);
void	mlxdg_remove_entry(t_game *g, char *name);

#endif