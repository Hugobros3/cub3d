/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:21:13 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:36:05 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_parser.h"

void	parse_vertex(char *l, t_list **verts)
{
	char	**split;
	t_v4	*v;

	split = ft_split(l, ' ');
	v = pv4(atof(split[1]), atof(split[2]), atof(split[3]), 0);
	ft_lstadd_back(verts, ft_lstnew(v));
	ft_freesplit(split);
}

void	parse_vertex_tex(char *l, t_list **texs)
{
	char	**split;
	t_v2	*v;

	split = ft_split(l, ' ');
	v = pv2(atof(split[1]), atof(split[2]));
	ft_lstadd_back(texs, ft_lstnew(v));
	ft_freesplit(split);
}

void	parse_vertex_norm(char *l, t_list **norms)
{
	char	**split;
	t_v4	*v;

	split = ft_split(l, ' ');
	v = pv4(atof(split[1]), atof(split[2]), atof(split[3]), 0);
	ft_lstadd_back(norms, ft_lstnew(v));
	ft_freesplit(split);
}

static void	parse_face2(char *l, t_iv3 *o)
{
	char	**split2;

	split2 = ft_split(l, '/');
	o->x = ft_atoi(split2[0]);
	if (split2[1])
		o->y = ft_atoi(split2[1]);
	if (split2[2])
		o->z = ft_atoi(split2[2]);
	ft_freesplit(split2);
}

void	parse_face(char *l, t_list **tris)
{
	char	**split;
	t_iv3	*o;
	int		i;

	i = 1;
	split = ft_split(l, ' ');
	while (split[i] && i <= 3)
	{
		o = piv3(0, 0, 0);
		if (ft_strchr(split[i], '/'))
			parse_face2(split[i], o);
		else
			o->x = ft_atoi(split[i]);
		ft_lstadd_back(tris, ft_lstnew(o));
		i++;
	}
	ft_freesplit(split);
}
