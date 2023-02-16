/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   holes_anim.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 03:29:39 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/14 16:39:47 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOLES_ANIM_H
# define HOLES_ANIM_H

# include "../intro.h"

typedef struct s_hanim
{
	float	fade;
	float	update_time;
	float	blink_time;
	t_bool	done;
}	t_hanim;

extern t_list	*g_lst;
extern t_hanim	g_hanim;

void	holes_anim_loop(t_game *g);
void	holes_anim_update_cells(t_game *g);

#endif