/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 23:14:42 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 15:23:09 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"
#include "mlx.h"
#include "cub3d.h"
#ifdef LINUX
# include <X11/Xlib.h>
#endif

t_game			*g_game;
t_map			g_map;
t_settings		g_settings;
t_data			g_data;
t_player		g_player;
t_list			*g_files_pool;

typedef char *	(*t_getter)(void *);

int	close_hook(void *p)
{
	(void)p;
	quit_cub3d();
	return (0);
}

#ifdef LINUX

static void	init_xthreads(void)
{
	XInitThreads();
}
#else

static void	init_xthreads(void)
{
}
#endif

static void	create_debug_entries(void)
{
	mlxdg_create_entry(g_game, "Player pos: ",
		(t_getter)mlxdg_entry_v2, &g_player.pos);
	mlxdg_create_entry(g_game, "Height: ",
		(t_getter)mlxdg_entry_float, &g_player.height);
	mlxdg_create_entry(g_game, "Rotation: ",
		(t_getter)mlxdg_entry_float, &g_player.rot);
	mlxdg_create_entry(g_game, "Lights count: ",
		(t_getter)mlxdg_entry_int, &g_data.lights_size);
	mlxdg_create_entry(g_game, "Client: ",
		(t_getter)mlxdg_entry_bool, &g_settings.is_client);
	mlxdg_create_entry(g_game, "Server: ",
		(t_getter)mlxdg_entry_bool, &g_settings.is_server);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf(RED"Invalid argument count !"RESET" (expected\
		 "YEL"1"RESET", had "YEL"%d"RESET")\n", argc - 1);
		return (ARGS_COUNT_ERROR);
	}
	g_game = mlxe_create_game(mlx_init(), iv2(832, 832), "CUB3D");
	mlx_hook(g_game->window, 17, 0, close_hook, NULL);
	init_xthreads();
	init();
	parse_map(read_map_file(argv[1]));
	g_data.map_save = duplicate_map(&g_map);
	create_debug_entries();
	start_intro();
	mlx_loop(g_game->mlx);
	return (0);
}
