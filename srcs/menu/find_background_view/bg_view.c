/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_view.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 11:14:45 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 15:35:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline static t_map_tile	get(t_iv2 p)
{
	return (g_map.data[p.x + p.y * g_map.size.x]);
}

typedef struct s_calcul_place
{
	t_v2	*p;
	t_v2	*final_pos;
	t_iv2	xy;
	t_iv2	i;
	float	r;
}	t_calcul_place;

static void	calcul_place2(t_calcul_place d)
{
	if ((d.i.x + d.i.y) > (d.p->x + d.p->y))
	{
		d.p->x = d.xy.y;
		d.p->y = d.i.x;
		d.final_pos->x = d.xy.x;
		d.final_pos->y = d.i.y;
		g_player.rot = d.r;
	}
}

static void	calcul_place(t_iv2 xy, float r, t_v2 *final_pos, t_v2 *p)
{
	t_iv2			i;
	int				j;
	t_calcul_place	d;

	i = iv2(0, 0);
	j = xy.y + (xy.x + i.x + 1) * g_map.size.x;
	while (j < vlen2i(g_map.size) && g_map.data[j]
		!= WALL && i.x < g_map.size.x)
	{
		i.x++;
		j = xy.y + (xy.x + i.x + 1) * g_map.size.x;
	}
	j = xy.x + (xy.y + i.y + 1) * g_map.size.x;
	while (j < vlen2i(g_map.size) && g_map.data[j]
		!= WALL && i.y < g_map.size.y)
	{
		i.y++;
		j = xy.x + (xy.y + i.y + 1) * g_map.size.x;
	}
	d = (t_calcul_place){p, final_pos, xy, i, r};
	calcul_place2(d);
}

static void	check_place(t_iv2 xy, t_v2 *final_pos, t_v2 *p)
{
	if (get(sub2i(xy, iv2(1, 0))) == WALL
		&& get(sub2i(xy, iv2(0, 1))) == WALL
		&& get(add2i(xy, iv2(1, 0))) == EMPTY
		&& get(add2i(xy, iv2(0, 1))) == EMPTY)
		calcul_place(xy, 45, final_pos, p);
	if (get(sub2i(xy, iv2(1, 0))) == WALL
		&& get(sub2i(xy, iv2(0, 1))) == EMPTY
		&& get(add2i(xy, iv2(1, 0))) == EMPTY
		&& get(add2i(xy, iv2(0, 1))) == WALL)
		calcul_place(xy, 315, final_pos, p);
	if (get(sub2i(xy, iv2(1, 0))) == EMPTY
		&& get(sub2i(xy, iv2(0, 1))) == WALL
		&& get(add2i(xy, iv2(1, 0))) == WALL
		&& get(add2i(xy, iv2(0, 1))) == EMPTY)
		calcul_place(xy, 135, final_pos, p);
	if (get(sub2i(xy, iv2(1, 0))) == EMPTY
		&& get(sub2i(xy, iv2(0, 1))) == EMPTY
		&& get(add2i(xy, iv2(1, 0))) == WALL
		&& get(add2i(xy, iv2(0, 1))) == WALL)
		calcul_place(xy, 225, final_pos, p);
}

void	find_place(void)
{
	t_iv2		xy;
	t_v2		final_pos;
	t_v2		p;

	p = v2(0, 0);
	xy = iv2(1, 1);
	final_pos = v2(0, 0);
	g_player.rot = 0;
	while (xy.y < g_map.size.y - 1)
	{
		while (xy.x < g_map.size.x - 1)
		{
			if (g_map.data[xy.x + xy.y * g_map.size.x] == EMPTY)
				check_place(xy, &final_pos, &p);
			xy.x++;
		}
		xy.x = 1;
		xy.y++;
	}
	g_player.pos = final_pos;
}
