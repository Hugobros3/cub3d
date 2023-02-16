/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:15:25 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:29:48 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "obj_parser.h"

typedef struct s_obj_parser
{
	t_mesh		*m;
	t_list		*verts;
	t_list		*texs;
	t_list		*norms;
	t_list		*tris;
	t_iv3		*a_tris;
	t_v4		*a_verts;
	t_v4		*a_norms;
	t_v2		*a_texs;
}	t_obj_parser;

static char	**read_and_split(char *filename)
{
	int		fd;
	char	*file;
	char	**lines;

	fd = open(filename, O_RDONLY);
	file = ft_readfile(fd, 4096);
	close(fd);
	lines = ft_split(file, '\n');
	return (lines);
}

static void	parse_obj_file_init(t_obj_parser *p)
{
	p->m = ft_malloc(sizeof(t_mesh));
	p->verts = NULL;
	p->tris = NULL;
	p->texs = NULL;
	p->norms = NULL;
}

t_mesh	*parse_obj_file(char *filename)
{
	char			**lines;
	t_obj_parser	p;
	int				j;

	parse_obj_file_init(&p);
	lines = read_and_split(filename);
	j = 0;
	while (lines[j])
	{
		if (!ft_strncmp(lines[j], "v ", 2))
			parse_vertex(lines[j], &p.verts);
		if (!ft_strncmp(lines[j], "vt ", 3))
			parse_vertex_tex(lines[j], &p.texs);
		if (!ft_strncmp(lines[j], "vn ", 3))
			parse_vertex_norm(lines[j], &p.norms);
		else if (!ft_strncmp(lines[j], "f ", 2))
			parse_face(lines[j], &p.tris);
		j++;
	}
	ft_freesplit(lines);
	parse_obj_file2(&p);
	parse_obj_file3(&p);
	parse_obj_file4(&p);
	return (p.m);
}
