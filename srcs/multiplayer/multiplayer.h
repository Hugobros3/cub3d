/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplayer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:33:04 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:43:36 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTIPLAYER_H
# define MULTIPLAYER_H

# include "cub3d.h"
# include <unistd.h>
# include <sys/socket.h>
# include <sys/un.h>
# include <pthread.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <signal.h>

# define CONNECTION_PORT 3212
# define BROADCAST_PORT 3213
# define MAX_UDP_SIZE 512

# define BASE_JOIN_EVENT "player_join"
# define BASE_LEAVE_EVENT "player_leave"
# define BASE_UPDATE_EVENT "player_update"
# define BASE_PING_EVENT "server_ping"
# define BASE_ANSWER_EVENT "server_answer"

# define SEND_FREQUENCY 10000

typedef enum e_player_type
{
	SEEKER,
	HIDER
}	t_player_type;

typedef enum e_event_type
{
	JOIN_EVENT,
	LEAVE_EVENT,
	UPDATE_EVENT,
	PING_EVENT,
	ANSWER_EVENT
}	t_event_type;

/*
join event: <size BASE_JOIN_EVENT player_name player_type>
leave event: <size BASE_LEAVE_EVENT player_name>
update event: <size BASE_UPDATE_EVENT player_name pos rot height flashlight>
ping event: <size BASE_PING_EVENT>
answer event: <size BASE_ANSWER_EVENT server_name current_players max_players>
*/

typedef struct s_event_base
{
	t_event_type	type;
}	t_event_base;

typedef struct s_join_event
{
	t_event_type	type;
	char			*player_name;
	t_player_type	t;
}	t_join_event;

typedef struct s_ping_event
{
	t_event_type	type;
}	t_ping_event;

typedef struct s_answer_event
{
	t_event_type	type;
	char			*server_name;
	int				players;
	int				max;
}	t_answer_event;

typedef struct s_leave_event
{
	t_event_type	type;
	char			*player_name;
}	t_leave_event;

typedef struct s_update_event
{
	t_event_type	type;
	char			*player_name;
	t_v2			pos;
	float			rot;
	float			height;
	t_bool			flashlight;
}	t_update_event;

typedef struct sockaddr_in	t_sockaddr_in;
typedef struct sockaddr		t_sockaddr;

typedef struct s_client_instance
{
	int				s;
	t_sockaddr_in	addr;
	int				run;
}	t_client_instance;

typedef struct s_m_player
{
	t_entity			*entity;
	t_light				*flashlight;
	t_client_instance	*i;
}	t_m_player;

typedef struct s_server
{
	int		player_count;
	t_list	*players;
}	t_server;

extern t_server				g_server;
extern t_list				*g_threads;
extern t_list				*g_sockets;
extern pthread_mutex_t		g_run_m;
extern t_bool				g_run;
extern t_image				*g_hider_tex;
extern t_image				*g_seeker_tex;

void		check_multi(t_game *g);
void		init_multiplayer(void);
void		stop_multiplayer(void);
void		request_multi_stop(void);
void		cleanup_multiplayer(void);

int			set_sock_timeout(int s, int time);

t_bool		get_is_running(void);

char		*get_addr_as_str(t_sockaddr *addr);

char		*build_join_event(t_join_event e, size_t *size);
char		*build_leave_event(t_leave_event e, size_t *size);
char		*build_update_event(t_update_event e, size_t *size);
char		*build_ping_event(size_t *size);
char		*build_answer_event(t_answer_event e, size_t *size);
void		handle_error(int err, t_client_instance *i);

int			read_next_event(int s, t_event_base **e);
int			read_next_event_from(int s, t_event_base **e,
				t_sockaddr_in *addr, socklen_t *len);
void		free_event(t_event_base *e);

int			cmp_player_instance(void *p1, void *p2);
void		register_new_player(t_join_event *event, t_client_instance *i);

int			sync_read(int s, void *buf, size_t size);
int			sync_write(int s, void *buf, size_t size);

int			ls_serv_create_socket(t_sockaddr_in *addr);

long long	ft_minlong(long long v1, long long v2);

void		free_sock(void *v);
void		free_mesh(t_mesh *m);
void		free_entity(t_entity *e);
void		free_m_player(void *v);
void		free_thread(void *v);
void		free_thread_force(void *v);

//=================Server=================
int			server_error(char *msg);
void		server_log(char *msg, ...);
int			start_server_main_thread(int s);
void		*client_instance_thread(void *data);
int			client_instance_receive_thread2(t_event_base *event,
				t_client_instance *i);
void		*client_instance_receive_thread(void *data);
void		*client_instance_send_thread(void *data);
int			send_map(t_client_instance *i);
int			send_all_files(t_client_instance *i);
void		handle_join_event(t_client_instance *i, t_join_event *e);
int			send_to_all(t_client_instance *except, t_event_base *e);
void		*server_broadcast_thread(void *d);
//========================================

//=================Client=================
int			client_error(char *msg);
void		client_log(char *msg, ...);
int			start_client_main_thread(int s, t_sockaddr_in addr);
void		*client_main_thread(void *data);
void		*client_receive_loop(void *data);
void		*client_send_loop(void *data);
int			receive_map(int s);
int			receive_all_files(int s);
int			receive_file(int s);
int			read_path(int s, char **path);
void		handle_error_client(int err);
//========================================
#endif