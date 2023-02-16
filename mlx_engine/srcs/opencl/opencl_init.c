/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:22:34 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 18:39:28 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxcl.h"

static cl_device_id	create_device(void)
{
	cl_platform_id	platform;
	cl_device_id	dev;
	cl_int			err;

	mlxe_log("Retrieving graphics card info...\n");
	mlxe_log("	->"YEL"GetPlatformIDs\n");
	fflush(stdout);
	err = clGetPlatformIDs(1, &platform, NULL);
	mlxe_log(GRN"		Done !\n"RESET);
	mlxcl_check_err(err, "Couldn't identify a platform");
	mlxe_log("	->"YEL"GetDeviceIDs\n");
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, NULL);
	if (err == CL_DEVICE_NOT_FOUND)
	{
		mlxe_log(CYN"		..using CPU..\n"RESET);
		err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &dev, NULL);
	}
	mlxe_log(GRN"		Done !\n"RESET);
	mlxcl_check_err(err, "Couldn't access any devices");
	return (dev);
}

//Initializes ui_main_prog
static void	ui_kernel_init(t_game *g)
{
	cl_int		err;
	cl_program	tmp;

	tmp = create_cl_program(g->cl_data, UI_KERN);
	err = clCompileProgram(tmp, 1, &g->cl_data->device,
			"", 0, NULL, NULL, NULL, NULL);
	if (err < 0)
		print_prog_log(g->cl_data, tmp);
	mlxcl_check_err(err, "Couldn't compile main UI prog !\n");
	g->cl_data->ui_main_prog = tmp;
	mlxe_log("Compiled UI main prog !\n");
}

static void	frame_buffer_init(t_game *g)
{
	g->frame_buffer = mlxcl_create_buffer(g->cl_data,
			CL_RW, sizeof(int) * vlen2i(g->size), NULL);
}

void	mlxcl_init(t_game *g)
{
	cl_int			err;

	g->cl_data = ft_malloc(sizeof(t_mlxcl_data));
	g->cl_data->device = create_device();
	g->cl_data->context = clCreateContext(NULL, 1,
			&g->cl_data->device, NULL, NULL, &err);
	mlxcl_check_err(err, "couldn't create a context");
	g->cl_data->queue = clCreateCommandQueue(g->cl_data->context,
			g->cl_data->device, 0, &err);
	g->cl_data->kernels = NULL;
	mlxcl_check_err(err, "couldn't create a queue");
	frame_buffer_init(g);
	ui_kernel_init(g);
	mlxcl_register_program(g->cl_data, MLXE_EVAL_IMG_KERN,
		"mlxe_eval_img", "");
	mlxcl_register_program(g->cl_data, MXLE_SET_ALPHA_KERN,
		"mlxe_set_alpha", "");
}
