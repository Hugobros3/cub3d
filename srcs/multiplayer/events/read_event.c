/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 00:00:30 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 09:32:26 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events_builder.h"
#include "../multiplayer.h"

static int	read_event_size(int s)
{
	int	n;
	int	out;

	n = read(s, &out, sizeof(int));
	if (n < 0)
		return (n);
	return (out);
}

static char	*receive_str(int s, int size)
{
	char	*str;
	int		total;
	int		n;

	str = ft_malloc(sizeof(char) * (size + 1));
	total = 0;
	n = 1;
	while (n > 0 && total < size)
	{
		n = read(s, str + total, sizeof(char) * (size - total));
		total += n;
	}
	if (n == 0)
	{
		free(str);
		return (NULL);
	}
	if (n < 0)
		return (NULL);
	str[size - 1] = '\0';
	return (str);
}

static int	read_event_error(int err, char *str, char **split)
{
	printf("--> Last event: %s\n", str);
	ft_freesplit(split);
	free(str);
	return (err);
}

int	read_next_event(int s, t_event_base **e)
{
	char			*str_received;
	char			**split;
	int				e_size;
	t_event_type	type;

	e_size = read_event_size(s);
	if (e_size == 0)
		return (0);
	if (e_size < 0)
	{
		printf("Event size error\n");
		return (-1);
	}
	str_received = receive_str(s, e_size);
	if (!str_received)
		return (-5);
	split = ft_split(str_received, ' ');
	type = parse_event_type(split[0]);
	if (type < 0)
		return (read_event_error(-3, str_received, split));
	if (parse_event(type, split + 1, e))
		return (read_event_error(-4, str_received, split));
	ft_freesplit(split);
	free(str_received);
	return (1);
}
