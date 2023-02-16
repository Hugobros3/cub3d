/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:48:18 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 18:39:03 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine_int.h"
#include "mlx_engine.h"

void	mlxcl_exec_kernel(t_game *g, t_mlxcl_prog *prog,
	int local_size, int global_size)
{
	cl_int	err;
	size_t	g_size;
	size_t	l_size;

	g_size = global_size;
	l_size = local_size;
	err = clEnqueueNDRangeKernel(g->cl_data->queue, prog->kernel, 1, NULL,
			&g_size, &l_size, 0, NULL, NULL);
	mlxcl_check_err(err, "Couldn't enqueue kernel '%s'\n", prog->name);
}

void	mlxcl_exec_kernel2(t_game *g, t_mlxcl_prog *prog,
	t_iv2 local_size, t_iv2 global_size)
{
	cl_int	err;
	size_t	*g_size;
	size_t	*l_size;

	g_size = (size_t[2]){global_size.x, global_size.y};
	l_size = (size_t[2]){local_size.x, local_size.y};
	err = clEnqueueNDRangeKernel(g->cl_data->queue, prog->kernel, 2, NULL,
			g_size, l_size, 0, NULL, NULL);
	mlxcl_check_err(err, "Couldn't enqueue kernel '%s'\n", prog->name);
}

void	mlxcl_exec_kernel3(t_game *g, t_mlxcl_prog *prog,
	t_iv3 local_size, t_iv3 global_size)
{
	cl_int	err;
	size_t	*g_size;
	size_t	*l_size;

	g_size = (size_t[3]){global_size.x, global_size.y, global_size.z};
	l_size = (size_t[3]){local_size.x, local_size.y, local_size.z};
	err = clEnqueueNDRangeKernel(g->cl_data->queue, prog->kernel, 2, NULL,
			g_size, l_size, 0, NULL, NULL);
	mlxcl_check_err(err, "Couldn't enqueue kernel '%s'\n", prog->name);
}
