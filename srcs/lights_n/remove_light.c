/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:26:40 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 01:37:29 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	delete_light(void *l)
{
	free(l);
}

void	remove_light(t_light *l)
{
	int	ret;

	ret = ft_lstremoveif(&g_data.lights, delete_light, ft_cmpaddr, l);
	if (ret != -1)
		g_data.lights_size -= ret;
}
