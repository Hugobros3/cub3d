/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:37:42 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:14:40 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSER_H
# define MAP_PARSER_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define MAP_SYMBOLS "10-|L \nNSEW"

typedef struct s_image	t_image;
typedef t_v4			t_color;
typedef struct s_list	t_list;
typedef struct s_entity	t_entity;
typedef int				t_bool;

typedef void			**t_v;
typedef void			(*t_f)(char *, char *, void *);

typedef struct s_symbol_info
{
	char	*symbol;
	char	*data;
}	t_symbol_info;

extern t_list			*g_symbols;

void			free_smbl(t_symbol_info smbl);

void			parse_map2(void);
void			check_map(void);

void			parse_img(char *symbol, char *file, t_image **addr);
void			parse_color(char *symbol, char *file, t_color *c);
void			parse_entity(char *symbol, char *str, t_entity **e);

void			parse_all_symbols(void);
t_symbol_info	find_symbol(char *smbl);

void			parse_smbl_required(char *name, void **addr,
					void (*f)(char *, char *, void *));
t_bool			parse_smbl_optional(char *name, void **addr,
					void (*f)(char *, char *, void *));

void			parse_textures(void);
void			allocate_map(void);
char			**skip_to_map(int *offset);
void			process_map(void);
#endif