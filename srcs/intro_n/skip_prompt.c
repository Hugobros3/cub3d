/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 01:25:42 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 10:59:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "intro.h"

void	skip_hook(t_game *g)
{
	t_image	*img;

	(void)g;
	if (is_key_pressed(g_game, KEY_ESCAPE) && g_intro.prompt)
		g_intro.global_intro_speed = INTRO_SPEED_UP;
	else
		g_intro.global_intro_speed = INTRO_SPEED;
	if (is_any_key_down(g_game) && !g_intro.prompt)
	{
		img = mlxe_render_text(g_game, g_settings.font,
				"Hold escape to skip", new_color(255, 255, 255, 127));
		g_intro.prompt = mlxe_create_ui(g_game->ui_root, "intro prompt");
		g_intro.prompt->pos = v2(0.01f, 0.91f);
		g_intro.prompt->size = div2(convert_size(img), v2(10, 10));
		g_intro.prompt->eval = mlxcl_get_prog(g_game->cl_data, MLXE_EVAL_IMG);
		g_intro.prompt->interactable = FALSE;
		g_intro.prompt->data_buffer = mlxcl_create_img_buffer(g_game->cl_data,
				img);
		free_img(img, g_game->mlx);
	}
}
