/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_3d.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 22:24:14 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/05 17:05:52 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_3D_H
# define ENGINE_3D_H

# include "mlx_engine.h"

# define PROJ_SIZE 1024

# define RESET_D_BUFFER_FILE "./srcs/entities/renderer_3d/reset_depth_buffer.cl"
# define RESET_D_BUFFER_KN "reset_depth_buffer"

# define PROJECTION_FILE "./srcs/entities/renderer_3d/projection.cl"
# define PROJECTION_KN "projection"

# define DRAW_TRIS_FILE "./srcs/entities/renderer_3d/draw_tris.cl"
# define DRAW_TRIS_KN "draw_tris"

typedef struct s_entity	t_entity;

typedef struct __attribute__ ((packed)) s_tris
{
	t_v4	p3d1;
	t_v4	p3d2;
	t_v4	p3d3;
	t_v4	world1;
	t_v4	world2;
	t_v4	world3;
	t_v4	normal1;
	t_v4	normal2;
	t_v4	normal3;
	t_v2	p1;
	t_v2	p2;
	t_v2	p3;
	t_v2	tex1;
	t_v2	tex2;
	t_v2	tex3;
	t_v2	bbox_min;
	t_v2	bbox_max;
	float	w1;
	float	w2;
	float	w3;
	int		rendered;
}	t_tris;

typedef struct s_renderer_3d
{
	cl_mem			depth_buffer;
	t_mlxcl_prog	*reset_d_buffer;
	t_mlxcl_prog	*proj_prog;
	t_mlxcl_prog	*draw_prog;
}	t_renderer_3d;

typedef struct s_mesh	t_mesh;

void	draw_3d_model(t_mesh *m, float rotation, t_v3 translation,
			t_image *tex);

void	projection(t_entity *e);
void	drawing(t_entity *e, t_iv2 start, t_iv2 end);

extern t_renderer_3d	g_renderer_3d;

#endif