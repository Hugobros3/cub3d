/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_buffers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:56:14 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 18:36:00 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxcl.h"

void	mlxcl_set_arg(t_mlxcl_prog *prog, int index, size_t size, void *buf)
{
	cl_int	err;

	err = clSetKernelArg(prog->kernel, index, size, buf);
	mlxcl_check_err(err,
		"Couldn't set kernel argument for prog %s at index %d\n",
		prog->name, index);
}

cl_mem	mlxcl_create_buffer(t_mlxcl_data *mlxcl,
	cl_mem_flags flags, size_t size, void *buffer)
{
	cl_mem	buf;
	cl_int	err;

	if (buffer)
		flags |= CL_MEM_COPY_HOST_PTR;
	buf = clCreateBuffer(mlxcl->context,
			flags,
			size, buffer, &err);
	mlxcl_check_err(err,
		"Couldn't make buffer of size %lu (data: %p)\n", size, buffer);
	return (buf);
}

void	mlxcl_write_buffer(t_mlxcl_data *mlxcl,
		cl_mem cl_buf, size_t size, void *buffer)
{
	clEnqueueWriteBuffer(mlxcl->queue, cl_buf,
		FALSE, 0, size, buffer, 0, NULL, NULL);
}
