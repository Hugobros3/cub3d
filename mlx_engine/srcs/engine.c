/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 14:18:08 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/09 05:24:45 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine_int.h"
#include "mlx_engine.h"

void	mlxe_put_img_to_window(t_game *g, t_image *img)
{
	ft_lstadd_back(&g->intern->imgs_to_win, ft_lstnew(img));
}
