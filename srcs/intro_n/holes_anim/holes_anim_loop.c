/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   holes_anim_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:38:32 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 01:31:44 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holes_anim.h"
#include "cub3d.h"

static int	holes_anim_update_timer(void)
{
	static float	timer = 0;

	if (timer < g_hanim.update_time / g_intro.global_intro_speed)
	{
		timer += g_game->d_time;
		return (0);
	}
	else
		timer = 0;
	return (1);
}

static int	try_place_hole(t_iv2 pos, t_iv2 offset)
{
	t_cell	*c;
	t_v2	pos2;
	t_v2	*h_pos;

	c = get_cell(add2i(pos, offset));
	if (c && c->tile == WALL && !c->flag)
	{
		c->flag = TRUE;
		pos2 = add2(iv2v2(pos), v2(0.5, 0.5));
		h_pos = pv2(0, 0);
		h_pos->x = pos2.x + offset.x / 2.0f;
		h_pos->y = pos2.y + offset.y / 2.0f;
		ft_lstadd_back(&g_map.holes, ft_lstnew(h_pos));
		return (1);
	}
	return (0);
}

static int	place_holes(t_iv2 pos)
{
	if (try_place_hole(pos, iv2(0, 1)))
		return (1);
	if (try_place_hole(pos, iv2(0, -1)))
		return (1);
	if (try_place_hole(pos, iv2(1, 0)))
		return (1);
	if (try_place_hole(pos, iv2(-1, 0)))
		return (1);
	return (0);
}

void	holes_anim_loop(t_game *g)
{
	t_iv2	pos;
	float	r1;
	float	r2;
	t_cell	*c;

	if (!holes_anim_update_timer())
		return ;
	r1 = ft_frand(mlxe_timestamp());
	r2 = ft_frand(mlxe_timestamp() + 10);
	pos = iv2(r1 * g_intro.size.x, r2 * g_intro.size.y);
	c = get_cell(pos);
	c->t = 1;
	if (c->tile != WALL && !c->infected && !c->blink)
	{
		if (place_holes(pos))
			c->is_hole = TRUE;
		c->blink = TRUE;
	}
	ft_lstadd_back(&g_lst, ft_lstnew(c));
	if (ft_lstsize(g_map.holes) == g_settings.holes_count)
	{
		mlxe_remove_loop_hook(g, holes_anim_loop);
		g_hanim.done = TRUE;
	}
}
