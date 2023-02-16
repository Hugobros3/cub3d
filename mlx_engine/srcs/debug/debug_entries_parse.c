/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_entries_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:19:00 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/27 14:21:15 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_menu.h"

char	*mlxdg_entry_float(float *f)
{
	return (ft_ftoa(*f));
}

char	*mlxdg_entry_bool(t_bool *b)
{
	if (*b)
		return (ft_strdup("TRUE"));
	return (ft_strdup("FALSE"));
}

char	*mlxdg_entry_int(int *f)
{
	return (ft_itoa(*f));
}

char	*mlxdg_entry_v2(t_v2 *v)
{
	char	*out;

	out = ft_ftoa(v->x);
	out = ft_str_append(out, " ", 1, 0);
	out = ft_str_append(out, ft_ftoa(v->y), 1, 1);
	return (out);
}

char	*mlxdg_entry_iv2(t_iv2 *v)
{
	char	*out;

	out = ft_itoa(v->x);
	out = ft_str_append(out, " ", 1, 0);
	out = ft_str_append(out, ft_itoa(v->y), 1, 1);
	return (out);
}
