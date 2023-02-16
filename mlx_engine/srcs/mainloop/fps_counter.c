/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 04:33:38 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 01:01:24 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine_int.h"
#include "mlx_engine.h"
#include <math.h>
#ifdef LINUX
# include <X11/Xlib.h>
# include "mlx_int.h"
#endif

static float	get_average_fps(t_game *g)
{
	int		i;
	float	result;

	result = 0;
	i = 0;
	while (i < FPS_COUNTER_MAX)
	{
		if (isnan(g->intern->average_fps[i]))
			break ;
		result += g->intern->average_fps[i];
		i++;
	}
	return (result / (i + 1));
}

void	init_fps_counter(t_game *g)
{
	int	i;

	i = 0;
	while (i < FPS_COUNTER_MAX)
	{
		g->intern->average_fps[i] = NAN;
		i++;
	}
	g->intern->fps_index = 0;
}

void	update_fps_counter(t_game *g)
{
	g->intern->average_fps[g->intern->fps_index] = (1 / g->unscaled_d_time);
	g->intern->fps_index++;
	if (g->intern->fps_index >= FPS_COUNTER_MAX)
		g->intern->fps_index = 0;
}

#ifdef OSX

void	update_win_name(t_game *g)
{
	static float	timer = 0.2f;
	char			*name;

	if (timer > 0.2f)
	{
		name = ft_malloc(sizeof(char) * 10);
		snprintf(name, sizeof(char) * 10, "%f", get_average_fps(g));
		name = ft_str_append(name, " FPS - ", 1, 0);
		name = ft_str_append(name, " (", 1, 0);
		name = ft_str_append(name, ft_itoa(g->size.x), 1, 1);
		name = ft_str_append(name, "/", 1, 0);
		name = ft_str_append(name, ft_itoa(g->size.y), 1, 1);
		name = ft_str_append(name, ") - ", 1, 0);
		name = ft_str_append(name, g->win_name, 1, 0);
		mlx_set_window_name(g->window, name);
		free(name);
		timer = 0;
	}
	timer += g->unscaled_d_time;
}
#else

void	update_win_name(t_game *g)
{
	static float	timer = 0.2f;
	char			*name;

	if (timer > 0.2f)
	{
		name = ft_malloc(sizeof(char) * 10);
		snprintf(name, sizeof(char) * 10, "%f", get_average_fps(g));
		name = ft_str_append(name, " FPS - ", 1, 0);
		name = ft_str_append(name, " (", 1, 0);
		name = ft_str_append(name, ft_itoa(g->size.x), 1, 1);
		name = ft_str_append(name, "/", 1, 0);
		name = ft_str_append(name, ft_itoa(g->size.y), 1, 1);
		name = ft_str_append(name, ") - ", 1, 0);
		name = ft_str_append(name, g->win_name, 1, 0);
		XStoreName(((t_xvar *)g->mlx)->display,
			((t_xvar *)g->mlx)->win_list->window, name);
		free(name);
		timer = 0;
	}
	timer += g->unscaled_d_time;
}
#endif