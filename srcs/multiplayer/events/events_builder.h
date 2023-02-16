/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_builder.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:03:50 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 08:32:05 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_BUILDER_H
# define EVENTS_BUILDER_H

# include "../multiplayer.h"

typedef struct s_join_event		t_join_event;
typedef struct s_leave_event	t_leave_event;
typedef struct s_update_event	t_update_event;

char			*float_to_char(float f);
float			char_to_float(char *f);

t_event_type	parse_event_type(char *e);
int				parse_event(t_event_type t, char **split, t_event_base **e);

int				parse_join_event(char **e, t_join_event **event);
int				parse_leave_event(char **e, t_leave_event **event);
int				parse_update_event(char **e, t_update_event **event);
int				parse_ping_event(char **e, t_ping_event **event);
int				parse_answer_event(char **e, t_answer_event **event);	

void			*finish_event(char *e, size_t *out_size);

void			free_update_event(t_update_event *e);
void			free_join_event(t_join_event *e);
void			free_leave_event(t_leave_event *e);
void			free_ping_event(t_ping_event *e);
void			free_answer_event(t_answer_event *e);

#endif