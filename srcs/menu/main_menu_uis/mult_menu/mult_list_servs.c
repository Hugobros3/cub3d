/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_list_servs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 23:03:24 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:35:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mult_menu.h"
#include "../../../multiplayer/multiplayer.h"

void	release_entry_button(t_game *g, t_ui *ui)
{
	(void)g;
	(void)ui;
	start_client((char *)ui->data);
	make_transition(NULL, start_game, NULL);
}

static void	add_serv_entry(t_available_server *s, float *offset)
{
	t_ui	*entry;
	char	*text;
	t_image	*img;

	entry = mlxe_create_ui(g_mult_root, "mult entry");
	text = ft_strdup(s->name);
	text = ft_str_append(text, " ", 1, 0);
	text = ft_str_append(text, ft_itoa(s->p_count), 1, 1);
	text = ft_str_append(text, "/", 1, 0);
	text = ft_str_append(text, ft_itoa(s->p_max), 1, 1);
	text = ft_str_append(text, " ", 1, 0);
	text = ft_str_append(text, get_addr_as_str(s->addr), 1, 0);
	img = mlxe_render_text(g_game, g_settings.font, text,
			new_color(255, 255, 255, 255));
	free(text);
	entry->size = div2(convert_size(img), v2(15, 15));
	entry->pos = v2(0.01, *offset);
	entry->data_buffer = mlxcl_create_img_buffer(g_game->cl_data, img);
	entry->eval = mlxcl_get_prog(g_game->cl_data, MLXE_EVAL_IMG);
	entry->write_data_each_frame = FALSE;
	entry->data = ft_strdup(get_addr_as_str(s->addr));
	entry->on_release = release_entry_button;
	*offset += convert_size(img).y + 0.01;
	free_img(img, g_game->mlx);
}

static void	release_list_button(t_game *g, t_ui *ui)
{
	t_list				*servs;
	t_list				*curr;
	float				offset;

	(void)g;
	(void)ui;
	servs = list_servers();
	if (!servs)
		return ;
	curr = servs;
	offset = 0.2f;
	while (curr)
	{
		add_serv_entry((t_available_server *)curr->content, &offset);
		curr = curr->next;
	}
	ft_lstclear(&servs, (void (*)(void *))free_t_available_server);
}

void	init_list_button(void)
{
	t_ui	*ret;
	t_image	*img;

	ret = mlxe_create_ui(g_mult_root, "mult list button");
	img = mlxe_render_text(g_game, g_settings.font,
			"List servers", new_color(255, 255, 255, 255));
	ret->size = div2(convert_size(img), v2(15, 15));
	ret->pos = v2(0.51, 0.01);
	ret->data_buffer = mlxcl_create_img_buffer(g_game->cl_data, img);
	ret->eval = mlxcl_get_prog(g_game->cl_data, MLXE_EVAL_IMG);
	ret->del = (void (*)(void *ui))free_img_ui;
	ret->on_release = release_list_button;
	free_img(img, g_game->mlx);
}
