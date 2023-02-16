/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:17:13 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 19:30:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycast.h"

t_ui	*g_minimap_ui;

static void	map_update(t_ui *ui)
{
	t_mlxcl_prog	*prog;

	(void)ui;
	prog = mlxcl_get_prog(g_game->cl_data, "eval_minimap");
	mlxcl_set_arg(prog, 5, sizeof(t_iv2), &g_map.size);
	mlxcl_set_arg(prog, 6, sizeof(t_v2), &g_player.pos);
	mlxcl_set_arg(prog, 7, sizeof(float), &g_player.rot);
}

static void	minimap_init2(t_ui *ui)
{
	mlxcl_set_arg(ui->eval, 5, sizeof(t_iv2), &g_map.size);
	mlxcl_set_arg(ui->eval, 6, sizeof(t_v2), &g_player.pos);
	mlxcl_set_arg(ui->eval, 7, sizeof(float), &g_player.rot);
}

void	minimap_init(void)
{
	t_ui	*ui;
	void	*data;
	size_t	size;

	ui = mlxe_create_ui(g_game->ui_root, "minimap");
	size = sizeof(int) * vlen2i(g_map.size);
	data = ft_malloc(size);
	ui->data = data;
	ft_memcpy(data, g_map.data, sizeof(int) * vlen2i(g_map.size));
	ui->pos = v2(0.02 * g_game->aspect_ratio, 0.02);
	ui->size = v2(0.15, 0.15);
	ui->eval = mlxcl_get_prog(g_game->cl_data, "eval_minimap");
	if (!ui->eval)
		ui->eval = mlxcl_register_program(g_game->cl_data,
				"srcs/ingame/minimap/minimap.cl", "eval_minimap", "");
	minimap_init2(ui);
	ui->data_size = size;
	ui->data_buffer = mlxcl_create_buffer(g_game->cl_data, CL_RD,
			size, ui->data);
	ui->write_data_each_frame = FALSE;
	ui->interactable = FALSE;
	ui->del = free;
	ui->update = map_update;
	g_minimap_ui = ui;
}
