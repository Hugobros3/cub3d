/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_engine_int.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:40:54 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 15:21:41 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_ENGINE_INT_H
# define MLX_ENGINE_INT_H

# include "libft.h"

# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include <ft2build.h>
# include FT_FREETYPE_H

# ifdef DEBUG
#  define __USE_GNU
# endif

# ifdef OSX
#  include "../minilibx/mlx.h"
#  include <OpenCL/cl.h>
# elif LINUX
#  include <mlx.h>
#  include <CL/cl.h>
# endif

# define UI_KERN "./mlx_engine/srcs/kernels/ui_kernel.cl"
# define MLXE_EVAL_IMG_KERN "./mlx_engine/srcs/kernels/mlxe_eval_img.cl"
# define MXLE_SET_ALPHA_KERN "./mlx_engine/srcs/kernels/mlxe_set_alpha.cl"

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"
# define MLXE_TAG "\x1B[35m[MLXE] \x1B[0m"

# define FPS_COUNTER_MAX 300

typedef struct s_font
{
	FT_Face		face;
	t_list		*chars;
	char		*path;
}	t_font;

typedef struct s_image			t_image;
typedef struct s_ui				t_ui;
typedef struct s_game			t_game;
typedef struct s_mlxcl_data		t_mlxcl_data;
typedef struct s_mlxcl_prog		t_mlxcl_prog;
typedef struct s_debug_entry	t_debug_entry;

typedef struct s_debug_menu
{
	t_bool			init;
	t_list			*entries;
	void			*font;
	int				index;
	t_mlxcl_prog	*graph;
	cl_mem			graph_data;
}	t_debug_menu;

# ifndef MLX_ENGINE_INTERN
#  define MLX_ENGINE_INTERN

typedef struct s_intern
{
	FT_Library		ft;
	t_image			*render_img;
	t_list			*loop_hooks;
	t_ui			*hovered_ui;
	t_list			*keys_down;
	t_list			*keys_down_frame;
	t_list			*imgs_to_win;
	t_list			*coroutines;
	float			average_fps[FPS_COUNTER_MAX];
	int				fps_index;
	t_debug_menu	debug_m;
}	t_intern;
# endif

void		mlxcl_init(t_game *g);
void		mlxe_init_ft_lib(t_game *game);
void		init_fps_counter(t_game *g);

void		init_inputs(t_game *g);
int			key_press(int keycode, t_game *g);
int			key_release(int keycode, t_game *g);

void		draw_ui(t_ui *ui, t_game *g);
void		update_ui_selection(t_game *game);

void		mlxe_log(char *msg, ...);

int			mlxe_mainloop(void *data);
void		update_time(t_game *g);
void		update_win_name(t_game *g);
void		exec_loop_hooks(t_game *g);
void		update_fps_counter(t_game *g);

void		debug_menu_update(t_game *g);
void		free_debug_entry(t_debug_entry *e);
void		init_debug_menu(t_game *g);

#endif