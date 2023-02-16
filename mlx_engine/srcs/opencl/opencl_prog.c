/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_prog.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:25:06 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 00:04:01 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxcl.h"

static int	cmp_prog(t_mlxcl_prog *p, char *str)
{
	return (!ft_strcmp(p->name, str));
}

t_mlxcl_prog	*mlxcl_get_prog(t_mlxcl_data *mlxcl, char *kernel_name)
{
	t_list	*result;

	result = ft_lstfind(mlxcl->kernels, cmp_prog, kernel_name);
	if (!result)
		return (NULL);
	return (result->content);
}
