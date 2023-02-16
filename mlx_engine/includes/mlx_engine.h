/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_engine.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 14:17:04 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 01:06:12 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_ENGINE_H
# define MLX_ENGINE_H

# include <sys/time.h>
# ifdef OSX
#  include "../minilibx/mlx.h"
#  include <OpenCL/cl.h>
# elif LINUX
#  include <mlx.h>
#  include <CL/cl.h>
# endif

# include "mlxe_keys.h"
# include "images.h"
# include "libft.h"

# include <ft2build.h>
# include FT_FREETYPE_H

# include <pthread.h>
# include <stdio.h>

# define MLXCL_ERROR -100
# define MLXE_EVAL_IMG "mlxe_eval_img"

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

# define CL_RD CL_MEM_READ_ONLY
# define CL_WR CL_MEM_WRITE_ONLY
# define CL_RW CL_MEM_READ_WRITE

//==================================================
typedef int					t_bool;
typedef struct s_game		t_game;
typedef struct s_ui			t_ui;
//==================================================

//==================================================
typedef struct s_mlxcl_prog
{
	cl_program	program;
	char		*name;
	cl_kernel	kernel;
}	t_mlxcl_prog;

typedef struct s_mlxcl_data
{
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	queue;
	t_list				*kernels;
	cl_program			ui_main_prog;
}	t_mlxcl_data;
//==================================================
# ifndef MLX_ENGINE_INTERN
#  define MLX_ENGINE_INTERN

typedef void				t_intern;

# endif

typedef void				(*t_ui_event)(t_game *g, t_ui *ui);
typedef struct s_ui
{
	t_ui			*parent;
	t_list			*childs;
	t_bool			active;
	t_bool			interactable;
	t_bool			clicked;
	t_bool			hovered;
	t_v2			pos;
	t_v2			size;
	float			rot;
	t_mlxcl_prog	*eval;
	void			(*update)(t_ui *ui);
	t_ui_event		on_click;
	t_ui_event		on_release;
	t_ui_event		on_hover;
	t_ui_event		on_exit;
	void			(*del)(void *data);
	void			*data;
	size_t			data_size;
	cl_mem			data_buffer;
	t_bool			write_data_each_frame;
	t_bool			block_del_on_clear;
	char			*name;
}	t_ui;
//==================================================
typedef void				(*t_loop_hook)(t_game *);
typedef struct s_game
{
	void				*mlx;
	void				*window;
	char				*win_name;
	t_iv2				size;
	cl_mem				frame_buffer;

	t_ui				*ui_root;

	t_intern			*intern;

	t_mlxcl_data		*cl_data;

	float				d_time;
	unsigned long long	last_time;
	float				unscaled_d_time;
	float				timescale;
	float				time;

	float				aspect_ratio;

	pthread_mutex_t		sychro_mutex;
}	t_game;
//==================================================

char			*mlxe_get_symbol(void *p);

//======================Debug=======================

void			mlxdg_free_debug_menu(t_game *g);
char			*mlxdg_entry_bool(t_bool *b);
char			*mlxdg_entry_float(float *f);
char			*mlxdg_entry_int(int *f);
char			*mlxdg_entry_v2(t_v2 *v);
char			*mlxdg_entry_iv2(t_iv2 *v);
void			mlxdg_create_entry(t_game *g, char *name,
					char *(*get)(void *), void *data);
void			mlxdg_remove_entry(t_game *g, char *name);

//==================================================

//====================Coroutines====================

typedef struct s_coroutine	t_coroutine;
typedef t_bool				(*t_update_coroutine)(t_coroutine *);
typedef void				(*t_end_coroutine)(t_coroutine *);

typedef struct s_coroutine
{
	void				*data;
	t_update_coroutine	update;
	t_end_coroutine		on_end;
}						t_coroutine;

//Adds a new coroutine
void			mlxe_start_coroutine(t_game *g, t_update_coroutine update,
					t_end_coroutine end, void *data);

//Removes and frees the coroutine c in g->coroutines
void			mlxe_destroy_coroutine(t_game *g, t_coroutine *c);

//Clears and destroys the coroutines in g->coroutines
void			mlxe_clear_coroutines(t_game *g);

//==================================================

//========================UI========================

//Creates a new ui object with default values 
t_ui			*mlxe_create_ui(t_ui *parent, char *name);

//Clears all uis currently registered (FREES DATA USING ui->del)
void			mlxe_clear_ui(t_game *g);

//Destroyes the ui object (FREES DATA USING ui->del)
void			mlxe_free_ui(void *dat);

//Removes the ui object from the registered (DOES NOT FREE DATA)
void			mlxe_remove_ui(t_game *g, t_ui *ui);

//==================================================

//======================-Game======================-

//Creates a new t_game object
t_game			*mlxe_create_game(void *mlx, t_iv2 size, char *title);

void			mlxe_free_game(t_game *g);

//Registers the hook
void			mlxe_add_loop_hook(t_game *g, t_loop_hook hook);

//Unregisters the hook
void			mlxe_remove_loop_hook(t_game *g, t_loop_hook hook);

//Clears the registered loop hooks (INCLUDES TWEENS)
void			mlxe_clear_loop_hooks(t_game *g);

//Put the image on top of everything
void			mlxe_put_img_to_window(t_game *g, t_image *img);

//Timetamp in microseconds
suseconds_t		mlxe_timestamp(void);

//==================================================

//======================-Input======================

//Returns the mouse position
t_iv2			mlxe_get_mouse_pos(t_game *g);

//Moves the mouse
void			mlxe_mouse_move(t_game *g, t_iv2 pos);

//Check if key <keycode> is pressed that frame
t_bool			is_key_down(t_game *g, int keycode);

//Check if key <keycode> is currently pressed
t_bool			is_key_pressed(t_game *g, int keycode);

//Returns TRUE if any key is currently pressed
t_bool			is_any_key_pressed(t_game *g);

//Returns TRUE if any key is pressed that frame
t_bool			is_any_key_down(t_game *g);

//==================================================

//=======================Text=======================

//Initialises the font at "path"
void			*mlxe_init_font(t_game *g, char *path, t_iv2 quality);

//Renders "text" using "font"
t_image			*mlxe_render_text(t_game *g, void *font,
					char *text, t_color col);

//Not working
void			mlxe_set_font_quality(void *font, t_iv2 pixel_size);

//Frees "font"
void			mlxe_free_font(void *font);

//==================================================

//======================OpenCL======================

//If err < 0, printf msg and format args and exit(-100)
void			mlxcl_check_err(cl_int err, char *msg, ...);

//Compiles the file "filename" and registers the resulting program
//to the list of programs.
t_mlxcl_prog	*mlxcl_register_program(t_mlxcl_data *mlxcl, char *filename,
					char *kernel_name, char *compiler_options);

//Compiles the string "src" and registers the resulting program
//to the list of programs.
t_mlxcl_prog	*mlxcl_register_program_source(t_mlxcl_data *mlxcl,
					const char *src, char *kernel_name);

//Compiles the file "filename" as a UI program.
//The specified program must contain a
//function <int4 draw(float2 uv, __global void *data, int hovered, int clicked)>
t_mlxcl_prog	*mlxcl_create_ui_program(t_game *g, char *filename,
					char *compile_args);

//Get a registered program by it's kernel name.
t_mlxcl_prog	*mlxcl_get_prog(t_mlxcl_data *mlxcl, char *kernel_name);

//Creates an OpenCL buffer.
cl_mem			mlxcl_create_buffer(t_mlxcl_data *mlxcl, cl_mem_flags flags,
					size_t size, void *buffer);

//Creates an img OpenCL buffer.
cl_mem			mlxcl_create_img_buffer(t_mlxcl_data *mlxcl, t_image *img);

//Writes "buffer" into the OpenCL buffer "cl_buf"
void			mlxcl_write_buffer(t_mlxcl_data *mlxcl, cl_mem cl_buf,
					size_t size, void *buffer);

//Sets the argument at index to buf
void			mlxcl_set_arg(t_mlxcl_prog *prog, int index,
					size_t size, void *buf);

//Enqueues a kernel (1D)
void			mlxcl_exec_kernel(t_game *g, t_mlxcl_prog *prog,
					int local_size, int global_size);

//Enqueues a kernel (2D)
void			mlxcl_exec_kernel2(t_game *g, t_mlxcl_prog *prog,
					t_iv2 local_size, t_iv2 global_size);

//Enqueues a kernel (3D)
void			mlxcl_exec_kernel3(t_game *g, t_mlxcl_prog *prog,
					t_iv3 local_size, t_iv3 global_size);

//Frees a t_mlxcl_data instance
void			mlxcl_free(t_mlxcl_data *mlxcl);

//==================================================

#endif