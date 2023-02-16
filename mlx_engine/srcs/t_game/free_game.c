/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:43:59 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 18:35:29 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine_int.h"
#include "mlx_engine.h"

static void	free_imgs_to_win(t_game *g, t_list *lst)
{
	t_list	*curr;

	curr = lst;
	while (curr)
	{
		free_img((t_image *)lst->content, g->mlx);
		curr = curr->next;
	}
	ft_lstclear(&lst, NULL);
}

static void	free_intern(t_game *g)
{
	free_img(g->intern->render_img, g->mlx);
	ft_lstclear(&g->intern->keys_down, free);
	ft_lstclear(&g->intern->keys_down_frame, free);
	ft_lstclear(&g->intern->loop_hooks, NULL);
	ft_lstclear(&g->intern->coroutines, free);
	free_imgs_to_win(g, g->intern->imgs_to_win);
	FT_Done_FreeType(g->intern->ft);
	mlxdg_free_debug_menu(g);
	free(g->intern);
}

static void	free_all_ui(t_ui *ui)
{
	t_list	*curr;
	t_list	*next;

	curr = ui->childs;
	while (curr)
	{
		next = curr->next;
		free_all_ui((t_ui *)curr->content);
		curr = next;
	}
	if (ui->del)
		ui->del(ui->data);
	if (ui->data_buffer)
		clReleaseMemObject(ui->data_buffer);
	ft_lstclear(&ui->childs, NULL);
	free(ui);
}

#ifdef LINUX

void	mlxe_free_game(t_game *g)
{
	free_all_ui(g->ui_root);
	free_intern(g);
	clReleaseMemObject(g->frame_buffer);
	mlxcl_free(g->cl_data);
	mlx_destroy_window(g->mlx, g->window);
	mlx_destroy_display(g->mlx);
	mlx_destroy(g->mlx);
	free(g->mlx);
	pthread_mutex_destroy(&g->sychro_mutex);
	free(g);
}
#endif
#ifdef OSX

void	mlxe_free_game(t_game *g)
{
	free_all_ui(g->ui_root);
	free_intern(g);
	clReleaseMemObject(g->frame_buffer);
	mlxcl_free(g->cl_data);
	mlx_destroy_window(g->mlx, g->window);
	free(g->mlx);
	pthread_mutex_destroy(&g->sychro_mutex);
	free(g);
}
#endif
