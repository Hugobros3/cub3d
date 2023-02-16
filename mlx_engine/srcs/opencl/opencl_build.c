/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 01:07:05 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 18:36:16 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxcl.h"

//Reads a file, and creates an opencl program from the file
cl_program	create_cl_program(t_mlxcl_data *mlxcl, char *filename)
{
	size_t		program_size;
	int			err;
	int			fd;
	char		*file;
	cl_program	p;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: couldn't read file '%s'\n", filename);
		exit(MLXCL_ERROR);
	}
	file = ft_readfile(fd, 42);
	program_size = ft_strlen(file);
	p = clCreateProgramWithSource(mlxcl->context, 1,
			(const char **)&file, &program_size, &err);
	free(file);
	mlxcl_check_err(err, "Couldn't create the program from '%s'\n",
		err, filename);
	close(fd);
	return (p);
}

t_mlxcl_prog	*mlxcl_register_program(t_mlxcl_data *mlxcl, char *filename,
	char *kernel_name, char *compiler_options)
{
	int				err;
	t_mlxcl_prog	*prog;

	prog = ft_malloc(sizeof(t_mlxcl_prog));
	prog->program = create_cl_program(mlxcl, filename);
	err = clBuildProgram(prog->program, 0, NULL, compiler_options, NULL, NULL);
	if (err < 0)
		print_prog_log(mlxcl, prog->program);
	mlxcl_check_err(err, "Couldn't build the program '%s' (kernel: '%s')\n",
		filename, kernel_name);
	prog->kernel = clCreateKernel(prog->program, kernel_name, &err);
	mlxcl_check_err(err, "Couldn't create kernel '%s' (from file: '%s')\n",
		kernel_name, filename);
	prog->name = kernel_name;
	ft_lstadd_back(&mlxcl->kernels, ft_lstnew(prog));
	return (prog);
}

#define ERROR_MSG1 "Couldn't create program from source:\n%s\n(kernel: '%s')\n"
#define ERROR_MSG2 "Couldn't build program from source:\
\n%s\n(specified kernel: '%s')\n"
#define ERROR_MSG3 "Couldn't create kernel '%s' from source:\n%s\n"

t_mlxcl_prog	*mlxcl_register_program_source(t_mlxcl_data *mlxcl,
	const char *str, char *kernel_name)
{
	size_t			program_size;
	int				err;
	t_mlxcl_prog	*prog;

	prog = ft_malloc(sizeof(t_mlxcl_prog));
	program_size = ft_strlen(str);
	prog->program = clCreateProgramWithSource(mlxcl->context, 1,
			(const char **)&str, &program_size, &err);
	mlxcl_check_err(err, ERROR_MSG1, str, kernel_name);
	err = clBuildProgram(prog->program, 0, NULL, "", NULL, NULL);
	if (err < 0)
		print_prog_log(mlxcl, prog->program);
	mlxcl_check_err(err, ERROR_MSG2, str, kernel_name);
	prog->kernel = clCreateKernel(prog->program, kernel_name, &err);
	mlxcl_check_err(err, ERROR_MSG3, kernel_name, str);
	prog->name = kernel_name;
	ft_lstadd_back(&mlxcl->kernels, ft_lstnew(prog));
	return (prog);
}

t_mlxcl_prog	*mlxcl_create_ui_program(t_game *g, char *filename,
	char *compile_args)
{
	int					err;
	t_mlxcl_prog		*prog;
	t_mlxcl_data		*mlxcl;
	cl_program			tmp;
	cl_program			*progs;

	mlxcl = g->cl_data;
	prog = ft_malloc(sizeof(t_mlxcl_prog));
	tmp = create_cl_program(mlxcl, filename);
	err = clCompileProgram(tmp, 1, &mlxcl->device, "", 0,
			NULL, NULL, NULL, NULL);
	if (err < 0)
		print_prog_log(mlxcl, tmp);
	mlxcl_check_err(err, "Couldn't compile UI program for file '%s'\n",
		filename);
	progs = (cl_program[2]){tmp, mlxcl->ui_main_prog};
	prog->program = clLinkProgram(mlxcl->context, 1, &mlxcl->device,
			compile_args, 2, progs, NULL, NULL, &err);
	mlxcl_check_err(err, "Couldn't link UI program for file '%s'\n", filename);
	clReleaseProgram(tmp);
	prog->kernel = clCreateKernel(prog->program, "ui_kernel", &err);
	mlxcl_check_err(err, "Couldn't create UI kernel for file '%s'\n", filename);
	prog->name = "__UI_PROGRAM";
	ft_lstadd_back(&mlxcl->kernels, ft_lstnew(prog));
	return (prog);
}
