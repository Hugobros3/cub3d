/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:43:44 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 01:01:53 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine_int.h"
#include "mlx_engine.h"

int	cmpkeycode(int *i1, int *i2)
{
	return (*i1 == *i2);
}

t_bool	is_key_down(t_game *g, int keycode)
{
	t_list	*result;

	result = ft_lstfind(g->intern->keys_down_frame, cmpkeycode, &keycode);
	if (result)
		return (1);
	else
		return (0);
}

t_bool	is_key_pressed(t_game *g, int keycode)
{
	t_list	*result;

	result = ft_lstfind(g->intern->keys_down, cmpkeycode, &keycode);
	if (result)
		return (1);
	else
		return (0);
}

t_bool	key_press(int keycode, t_game *g)
{
	int	*n;

	if (!ft_lstfind(g->intern->keys_down_frame, cmpkeycode, &keycode))
	{
		n = ft_malloc(sizeof(int));
		*n = keycode;
		ft_lstadd_back(&g->intern->keys_down_frame, ft_lstnew(n));
	}
	if (!ft_lstfind(g->intern->keys_down, cmpkeycode, &keycode))
	{
		n = ft_malloc(sizeof(int));
		*n = keycode;
		ft_lstadd_back(&g->intern->keys_down, ft_lstnew(n));
	}
	return (0);
}

int	key_release(int keycode, t_game *g)
{
	ft_lstremoveif(&g->intern->keys_down, free, cmpkeycode, &keycode);
	ft_lstremoveif(&g->intern->keys_down_frame, free, cmpkeycode, &keycode);
	return (0);
}
