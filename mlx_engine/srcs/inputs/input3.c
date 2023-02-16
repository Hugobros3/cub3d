/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 01:01:43 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 01:02:00 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine_int.h"
#include "mlx_engine.h"

t_bool	is_any_key_pressed(t_game *g)
{
	if (ft_lstsize(g->intern->keys_down))
		return (TRUE);
	return (FALSE);
}

t_bool	is_any_key_down(t_game *g)
{
	if (ft_lstsize(g->intern->keys_down_frame))
		return (TRUE);
	return (FALSE);
}
