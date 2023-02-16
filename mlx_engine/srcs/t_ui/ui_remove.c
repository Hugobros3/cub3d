/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 23:11:19 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 18:35:29 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe_ui.h"

static void	clear_ui(t_ui *ui)
{
	t_list	*curr;
	t_list	*next;
	t_list	*result;

	if (ui->block_del_on_clear)
		return ;
	curr = ui->childs;
	while (curr)
	{
		next = curr->next;
		clear_ui((t_ui *)curr->content);
		curr = next;
	}
	if (ui->parent)
	{
		result = ft_lstfind(ui->parent->childs, ft_cmpaddr, ui);
		if (result)
		{
			mlxe_log(RED"Removing"RESET" ui '%s' at address "YEL"%p"RESET"\n",
				((t_ui *)result->content)->name, result->content);
			ft_lstremove(&ui->parent->childs, result, mlxe_free_ui);
		}
	}
}

void	mlxe_clear_ui(t_game *g)
{
	g->intern->hovered_ui = NULL;
	clear_ui(g->ui_root);
}

//Careful where you call that. mlxe_remove_ui before !
void	mlxe_free_ui(void *dat)
{
	t_ui	*ui;

	ui = (t_ui *)dat;
	if (ui->del)
	{
		printf("%s\n", ui->name);
		fflush(stdout);
		ui->del(ui->data);
	}
	if (ui->data_buffer)
		clReleaseMemObject(ui->data_buffer);
	free(ui->name);
	free(ui);
}

void	mlxe_remove_ui(t_game *g, t_ui *ui)
{
	if (g->intern->hovered_ui == ui)
		g->intern->hovered_ui = NULL;
	mlxe_log(RED"Removing"RESET" ui '%s' at address "YEL"%p"RESET"\n",
		ui->name, ui);
	ft_lstremoveif(&ui->parent->childs, mlxe_free_ui, ft_cmpaddr, ui);
}
