/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_symbols.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:18:04 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 16:01:08 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"
#include "cub3d.h"

void	free_smbl(t_symbol_info smbl)
{
	free(smbl.data);
	free(smbl.symbol);
}

t_symbol_info	find_symbol(char *smbl)
{
	t_symbol_info	inf;
	t_list			*curr;

	curr = g_symbols;
	while (curr)
	{
		inf.symbol = ft_substr(curr->content, 0, ft_strlen(smbl));
		inf.data = ft_substr(curr->content, ft_strlen(smbl) + 1,
				ft_strlen(curr->content) - ft_strlen(smbl) - 1);
		if (!ft_strncmp(smbl, inf.symbol, ft_strlen(smbl) + 1))
		{
			ft_lstremove(&g_symbols, curr, free);
			return (inf);
		}
		free(inf.symbol);
		free(inf.data);
		curr = curr->next;
	}
	inf.symbol = 0;
	inf.data = 0;
	return (inf);
}

void	parse_smbl_required(char *name, void **addr,
	void (*f)(char *, char *, void *))
{
	t_symbol_info	smbl;

	smbl = find_symbol(name);
	if (!smbl.data)
	{
		ft_printf(RED"Error"RESET": symbol %s is required\n", name);
		exit(SYMBOL_ERROR);
	}
	f(smbl.symbol, smbl.data, addr);
	free_smbl(smbl);
}

t_bool	parse_smbl_optional(char *name, void **addr,
	void (*f)(char *, char *, void *))
{
	t_symbol_info	smbl;

	smbl = find_symbol(name);
	if (!smbl.data)
		return (FALSE);
	f(smbl.symbol, smbl.data, addr);
	free_smbl(smbl);
	return (TRUE);
}
