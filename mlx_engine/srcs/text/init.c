/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:05:04 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/24 16:05:12 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textbuilder.h"

void	mlxe_init_ft_lib(t_game *game)
{
	if (FT_Init_FreeType(&game->intern->ft))
		ft_printf("Error loading FreeType library !\n");
}
