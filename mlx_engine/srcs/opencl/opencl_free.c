/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:24:03 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 18:35:29 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxcl.h"

static void	mlxcl_free_kernel(void *data)
{
	t_mlxcl_prog	*p;

	p = (t_mlxcl_prog *)data;
	clReleaseKernel(p->kernel);
	clReleaseProgram(p->program);
	free(p);
}

void	mlxcl_free(t_mlxcl_data *mlxcl)
{
	ft_lstclear(&mlxcl->kernels, mlxcl_free_kernel);
	clReleaseProgram(mlxcl->ui_main_prog);
	clReleaseCommandQueue(mlxcl->queue);
	clReleaseContext(mlxcl->context);
	clReleaseDevice(mlxcl->device);
	free(mlxcl);
}
