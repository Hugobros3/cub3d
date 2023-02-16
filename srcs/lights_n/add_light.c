/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 00:21:58 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/27 13:35:52 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_light	*add_light(t_light new_light)
{
	t_light	*tmp;

	tmp = ft_memdup(&new_light, sizeof(t_light));
	ft_lstadd_back(&g_data.lights, ft_lstnew(tmp));
	g_data.lights_size++;
	update_lights();
	return (tmp);
}

void	map_add_light(t_v2 pos)
{
	t_light	new_light;

	new_light.col = v4(0.8, 1, 0.8, 0);
	new_light.pos = v4(pos.x, 0.5, pos.y, 0);
	new_light.radius = 180;
	new_light.size = 10;
	new_light.dir = v4(0, -1, 0, 0);
	new_light.is_spotlight = FALSE;
	ft_lstadd_back(&g_map.lights,
		ft_lstnew(ft_memdup(&new_light, sizeof(t_light))));
	g_map.lights_size++;
}

void	copy_map_lights(void)
{
	t_list	*curr;

	curr = g_map.lights;
	while (curr)
	{
		ft_lstadd_back(&g_data.lights,
			ft_lstnew(ft_memdup(curr->content, sizeof(t_light))));
		curr = curr->next;
	}
	ft_lstclear(&g_map.lights, free);
	update_lights();
}
