/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_chain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 01:35:24 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 15:59:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"
#include "cub3d.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

t_list	*g_symbols;

static void	null_terminate(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	str[i] = '\0';
}

char	**read_map_file(char *map_path)
{
	int		fd;
	char	*str;
	t_list	*lst;
	char	**out;

	fd = open(map_path, O_RDONLY);
	lst = NULL;
	str = ft_gnl(fd);
	while (str)
	{
		null_terminate(str);
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(str)));
		str = ft_gnl(fd);
	}
	close(fd);
	out = (char **)ft_lst_to_array_pointers(lst);
	ft_lstclear(&lst, NULL);
	return (out);
}

void	parse_map(char **str)
{
	int		i;
	int		j;
	t_list	*new;

	g_map.str = str;
	g_symbols = NULL;
	i = 0;
	while (g_map.str[i] && !ft_isdigit(g_map.str[i][0]))
		i++;
	j = 0;
	while (j < i)
	{
		if (!g_map.str[j][0] || g_map.str[j][0] == '#')
		{
			j++;
			continue ;
		}
		new = ft_lstnew(ft_strdup(g_map.str[j]));
		ft_lstadd_back(&g_symbols, new);
		ft_printf("Symbol indentified: %s\n", new->content);
		j++;
	}
	parse_all_symbols();
	parse_map2();
}

void	parse_all_symbols(void)
{
	t_entity		*e;
	int				i;

	parse_textures();
	i = 0;
	while (i < ENTITY_LIMIT)
	{
		e = NULL;
		parse_smbl_optional("E", (t_v) & e, (t_f)parse_entity);
		if (!e)
			break ;
		ft_lstadd_back(&g_data.entities,
			ft_lstnew(e));
	}
	ft_lstclear(&g_symbols, free);
}
