/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verifier.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 07:21:17 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 01:31:55 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_VERIFIER_H
# define MAP_VERIFIER_H

# include "../intro.h"

# define VERIF_ANIM_BASE_TIME 0.03f

typedef struct s_verif_anim
{
	float	verif_anim_time;
	t_iv2	last_cell_infec;
	t_ui	*done_ui;
}	t_verif_anim;

typedef struct s_done_anim
{
	t_color	c;
	t_iv2	size;
	t_v2	p;
	float	d;
}	t_done_anim;

extern t_done_anim	g_done_anim;
extern t_verif_anim	g_vanim;

void	verif_animation(t_game *g);
int		verif_algo(void);
int		check_wall(t_iv2 p);

void	start_done_anim(t_iv2 last_infect);
void	done_animation(t_game *g);

#endif