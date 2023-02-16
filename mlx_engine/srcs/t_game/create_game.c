/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:16:50 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 00:33:16 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine_int.h"
#include "mlx_engine.h"

static void	init_intern(t_game *g)
{
	g->intern = ft_malloc(sizeof(t_intern));
	g->intern->render_img = new_img(g->mlx, g->size);
	g->intern->loop_hooks = NULL;
	g->intern->keys_down = NULL;
	g->intern->keys_down_frame = NULL;
	g->intern->imgs_to_win = NULL;
	g->intern->coroutines = NULL;
	g->intern->hovered_ui = NULL;
	g->intern->debug_m.init = FALSE;
	printf(CYN"Initializing"RESET" fps counter (FPS_COUNTER_MAX: "YEL"%d"
		RESET")...\n", FPS_COUNTER_MAX);
	init_fps_counter(g);
	mlxe_init_ft_lib(g);
	init_debug_menu(g);
}

static void	init_game(t_game *g, char *title, void *mlx, t_iv2 size)
{
	struct timeval		tv;
	unsigned long long	ms;

	gettimeofday(&tv, NULL);
	ms = (unsigned long long)(tv.tv_sec) *1000
		+ (unsigned long long)(tv.tv_usec) / 1000;
	pthread_mutex_init(&g->sychro_mutex, NULL);
	g->win_name = title;
	g->mlx = mlx;
	g->size = size;
	g->window = mlx_new_window(mlx, size.x, size.y, title);
	g->d_time = 0;
	g->time = 0;
	g->unscaled_d_time = 0;
	g->last_time = ms;
	g->timescale = 1;
	g->aspect_ratio = g->size.x / g->size.y;
}

static void	init_root_ui(t_game *g)
{
	g->ui_root = mlxe_create_ui(NULL, "ROOT");
	g->ui_root->active = TRUE;
	g->ui_root->pos = v2(0, 0);
	g->ui_root->size = v2(1, 1);
}

t_game	*mlxe_create_game(void *mlx, t_iv2 size, char *title)
{
	t_game	*g;

	if (size.x % 32 != 0 || size.y % 32 != 0)
	{
		printf(RED"Error"RESET": window size must be divisble by "
			YEL"32"RESET" !\n");
		exit(1);
	}
	g = ft_malloc(sizeof(t_game));
	printf(CYN"Initializing"RESET" game...\n");
	init_game(g, title, mlx, size);
	printf(CYN"Initializing"RESET" intern...\n");
	mlxcl_init(g);
	init_intern(g);
	init_root_ui(g);
	printf(CYN"Initializing"RESET" inputs...\n");
	init_inputs(g);
	mlx_loop_hook(g->mlx, mlxe_mainloop, g);
	return (g);
}
