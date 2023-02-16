/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:56:00 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 15:31:16 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSITION_H
# define TRANSITION_H

# include "cub3d.h"

# define EVAL_FADE "./srcs/transition_n/fade.cl"

typedef struct s_transition
{
	t_ui	*ui;
	void	(*halfway)();
	void	(*done)();
	float	fade;
}	t_transition;

extern t_transition	g_transition;

void	fade_out_start(void);
void	fade_in_start(void);

t_bool	fade_out_loop(t_coroutine *c);
t_bool	fade_in_loop(t_coroutine *c);

#endif