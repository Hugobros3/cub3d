/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 01:18:20 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 15:11:18 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx_engine.h" 

# define ENTITY_LIMIT 100
# define MAIN_FONT "assets/Zag Regular.ttf"

# define MAX_PLAYERS 20
# define HOLES_COUNT 10
# define HOSTNAME_SIZE 20
# define DOOR_OPEN_RADIUS 2
# define DOOR_OPEN_SPEED 3
# define FLASHLIGHT_SIZE 10

typedef enum e_error_codes
{
	SYMBOL_ERROR,
	MAP_ERROR,
	ARGS_COUNT_ERROR
}	t_error_codes;

typedef struct s_tris	t_tris;
typedef struct s_mesh
{
	t_tris	*triangles;
	int		triangles_count;
	cl_mem	tris_buffer;
}	t_mesh;

typedef struct s_entity
{
	t_v2	pos;
	float	height;
	float	rotation;
	t_mesh	*m;
	t_image	*texture;
	cl_mem	tex_buf;
	t_bool	is_rat;
	char	name[HOSTNAME_SIZE + 3];
}	t_entity;

typedef struct __attribute__ ((packed)) s_light
{
	t_v4	pos;
	t_v4	col;
	t_v4	dir;
	float	radius;
	float	size;
	t_bool	is_spotlight;
}	t_light;

typedef struct s_door
{
	t_v2	pos;
	float	open_amount;
	t_bool	flipped;
}	t_door;

typedef struct s_map
{
	char	**str;
	t_iv2	size;
	int		*data;
	t_list	*holes;
	t_bool	is_valid;
	t_iv2	spawn_pos;
	float	spawn_rot;
	t_door	*doors;
	int		doors_size;
	t_list	*lights;
	int		lights_size;
	t_image	*no;
	t_image	*so;
	t_image	*ea;
	t_image	*we;
	t_image	*floor;
	t_image	*ceil;
	t_image	*door;
	t_color	floor_col;
	t_color	ceil_col;
	t_list	*files_used;
}	t_map;

typedef enum e_map_tile
{
	WALL = 0,
	EMPTY = 1,
	DOOR = 100
}	t_map_tile;

typedef struct s_settings
{
	float			player_height;
	float			vertical_vel;

	void			*font;
	int				holes_count;

	t_bool			ingame_initialized;

	t_bool			is_server;
	t_bool			is_client;

	t_bool			mouse_lock;
	t_bool			mouse_controls;
	float			mouse_sensi;
}	t_settings;

typedef struct s_data
{
	t_list	*multiplayer_entities;
	t_list	*entities;
	t_list	*lights;
	int		lights_size;
	cl_mem	lights_buf;
	t_bool	flashlight;
	t_light	*flashlight_data;
	char	hostname[HOSTNAME_SIZE + 3];
	t_map	*map_save;
	int		player_count;
}	t_data;

typedef struct __attribute__((packed)) s_player
{
	t_v2	pos;
	float	rot;
	float	height;
	float	fov;
	float	up_rot;
}	t_player;

typedef struct sockaddr	t_sockaddr;

typedef struct s_available_server
{
	char		*name;
	int			p_count;
	int			p_max;
	t_sockaddr	*addr;
}	t_available_server;

typedef struct __attribute__((packed)) s_slider_info
{
	t_iv4	c1;
	t_iv4	c2;
	float	handle_size;
	float	border_size;
	float	line_size;
	void	(*set)(float v);
	float	(*get)(void);
}	t_slider_info;

typedef struct __attribute__((packed)) s_boolbutton_info
{
	t_iv4	c1;
	t_iv4	c2;
	t_bool	v;
	void	(*set)(t_bool v);
	t_bool	(*get)(void);
}	t_boolbutton_info;

extern t_settings		g_settings;
extern t_player			g_player;
extern t_data			g_data;
extern t_game			*g_game;
extern t_map			g_map;
extern t_list			*g_files_pool;

t_ui		*create_slider(t_ui *parent, t_v2 pos,
				t_v2 size, t_slider_info infos);
t_ui		*create_bool_button(t_ui *parent, t_v2 pos,
				t_v2 size, t_boolbutton_info infos);

void		free_img_ui(t_image *img);
t_v2		convert_size(t_image *img);

t_list		*list_servers(void);
void		free_t_available_server(t_available_server *s);

void		free_m_player(void *v);

void		init(void);
void		get_user_name(void);

char		**read_map_file(char *map_path);
void		parse_map(char **str);
t_map		*duplicate_map(t_map *m);

t_mesh		*parse_obj_file(char *filename);
void		init_renderer(void);
void		init_renderer_first(void);

void		init_transition(void);
void		make_transition(void (*start)(), void (*halfway)(), void (*done)());

void		start_intro(void);
void		load_menu(void);
void		menu_background_loop(t_game *g);
void		tmp_multi(t_game *g);
void		start_game(void);
void		game_loop(t_game *g);

void		update_player(void);
void		handle_mouse_control(void);

void		escape_menu_init(void);
void		show_escape_menu(void);
void		hide_escape_menu(void);
void		switch_escape_menu(void);

void		switch_option_menu(void (*f)());
void		init_option_menu(void);

void		raycast_init(void);
void		raycast(void);
void		raycast_cleanup(void);

void		cleanup(void);
void		quit_cub3d(void);

void		remove_light(t_light *l);
void		map_add_light(t_v2 pos);
t_light		*add_light(t_light new_light);
void		update_lights(void);
void		delete_light(void *l);
void		copy_map_lights(void);

void		update_doors(void);

void		get_sprite_pos(t_entity *e, t_iv2 *start_pos, t_iv2 *end_pos);
t_v4		get_sprite_rot(t_entity *e);
void		draw_entities(void);
t_entity	*create_entity(char *obj_file, t_image *texture, t_bool is_rat);

void		start_client(char *ip);
void		start_server(void);
void		init_multiplayer(void);
void		stop_multiplayer(void);
void		stop_multi_loop(t_game *g);

void		cleanup_map(t_map *map);

# ifdef LINUX

int			add_file(char *filename, int fd);
# else

int			add_file(char *filename, char *tmp, int fd);
# endif

void		cleanup_file_pool(void);
int			get_file_fd(char *filename);
char		*get_file_name(int fd);
int			fp_open(char *filepath, int flags);

#endif
