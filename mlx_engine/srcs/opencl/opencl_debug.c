/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:18:59 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 18:35:53 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxcl.h"
#include <stdarg.h>

void	print_prog_log(t_mlxcl_data *data, cl_program prog)
{
	char	*program_log;
	size_t	log_size;

	clGetProgramBuildInfo(prog, data->device, CL_PROGRAM_BUILD_LOG,
		0, NULL, &log_size);
	program_log = (char *)malloc(log_size + 1);
	program_log[log_size] = '\0';
	clGetProgramBuildInfo(prog, data->device, CL_PROGRAM_BUILD_LOG,
		log_size + 1, program_log, NULL);
	ft_printf("%s\n", program_log);
	free(program_log);
}

void	mlxcl_check_err(cl_int err, char *msg, ...)
{
	va_list	l;

	if (err < 0)
	{
		va_start(l, msg);
		ft_printf(MLXE_TAG RED "An opencl error occured "
			YEL"(%d)"RESET":\n\t", err);
		vprintf(msg, l);
		va_end(l);
		exit(err);
	}
}
