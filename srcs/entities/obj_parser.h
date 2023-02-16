/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:21:18 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:30:39 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_PARSER_H
# define OBJ_PARSER_H

# include "engine_3d.h"
# include "cub3d.h"

void	parse_vertex(char *l, t_list **verts);
void	parse_vertex_tex(char *l, t_list **texs);
void	parse_vertex_norm(char *l, t_list **norms);
void	parse_face(char *l, t_list **tris);

typedef struct s_obj_parser	t_obj_parser;

void	parse_obj_file2(t_obj_parser *p);
void	parse_obj_file3(t_obj_parser *p);
void	parse_obj_file4(t_obj_parser *p);

#endif