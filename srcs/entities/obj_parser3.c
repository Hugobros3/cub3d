/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:29:19 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:30:00 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	parse_obj_file2(t_obj_parser *p)
{
	p->a_verts = ft_lst_to_array(p->verts, sizeof(t_v4));
	p->a_tris = ft_lst_to_array(p->tris, sizeof(t_iv3));
	p->a_texs = ft_lst_to_array(p->texs, sizeof(t_v2));
	p->a_norms = ft_lst_to_array(p->norms, sizeof(t_v4));
	p->m->triangles_count = ft_lstsize(p->tris) / 3;
	p->m->triangles = ft_malloc(sizeof(t_tris) * p->m->triangles_count);
}

void	parse_obj_file3(t_obj_parser *p)
{
	int				t;
	int				i;

	i = 0;
	t = 0;
	while (t < p->m->triangles_count)
	{
		p->m->triangles[t].p3d1 = p->a_verts[p->a_tris[i].x - 1];
		p->m->triangles[t].p3d2 = p->a_verts[p->a_tris[i + 1].x - 1];
		p->m->triangles[t].p3d3 = p->a_verts[p->a_tris[i + 2].x - 1];
		p->m->triangles[t].tex1 = p->a_texs[p->a_tris[i].y - 1];
		p->m->triangles[t].tex2 = p->a_texs[p->a_tris[i + 1].y - 1];
		p->m->triangles[t].tex3 = p->a_texs[p->a_tris[i + 2].y - 1];
		p->m->triangles[t].normal1 = p->a_norms[p->a_tris[i].z - 1];
		p->m->triangles[t].normal2 = p->a_norms[p->a_tris[i + 1].z - 1];
		p->m->triangles[t].normal3 = p->a_norms[p->a_tris[i + 2].z - 1];
		t++;
		i += 3;
	}
}

void	parse_obj_file4(t_obj_parser *p)
{
	ft_lstclear(&p->verts, free);
	ft_lstclear(&p->tris, free);
	ft_lstclear(&p->texs, free);
	ft_lstclear(&p->norms, free);
	free(p->a_verts);
	free(p->a_tris);
	free(p->a_texs);
	free(p->a_norms);
	p->m->tris_buffer = mlxcl_create_buffer(g_game->cl_data,
			CL_RW, sizeof(t_tris)
			* p->m->triangles_count, p->m->triangles);
}
