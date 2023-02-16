/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:01:37 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/22 01:27:54 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_entity	*create_entity(char *obj_file, t_image *texture, t_bool is_rat)
{
	t_entity	*e;

	e = ft_malloc(sizeof(t_entity));
	e->m = parse_obj_file(obj_file);
	e->texture = texture;
	e->tex_buf = mlxcl_create_img_buffer(g_game->cl_data, e->texture);
	e->rotation = 0;
	if (is_rat)
		e->height = 0.5f;
	else
		e->height = 0;
	e->pos = v2(0, 0);
	e->is_rat = is_rat;
	return (e);
}
