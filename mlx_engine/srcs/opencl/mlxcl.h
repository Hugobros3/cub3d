/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxcl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:19:51 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/25 23:32:22 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXCL_H
# define MLXCL_H

# include "mlx_engine_int.h"
# include "mlx_engine.h"

void		print_prog_log(t_mlxcl_data *data, cl_program prog);
void		mlxcl_check_err(cl_int err, char *msg, ...);

cl_program	create_cl_program(t_mlxcl_data *mlxcl, char *filename);

#endif