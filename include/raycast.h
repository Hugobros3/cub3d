/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:44:03 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/24 15:40:52 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "cub3d.h"

# define RAYCAST_KN "./srcs/raycast/raycast.cl"
# define RAYCAST_KN_NAME "raycast"
# define RAYCAST_DRAW_KN "./srcs/raycast/raycast_draw.cl"
# define RAYCAST_DRAW_KN_NAME "raycast_draw"

typedef struct s_raycast
{
	t_mlxcl_prog		*raycast_prog;
	t_mlxcl_prog		*raycast_draw_prog;
	cl_mem				map_buffer;
	cl_mem				dists_buffer;
	cl_mem				ray_data_buffer;
	pthread_mutex_t		map_buffer_m;
	cl_mem				doors_buffer;
}	t_raycast;

typedef struct s_raycast_textures
{
	cl_mem	no;
	cl_mem	so;
	cl_mem	ea;
	cl_mem	we;
	cl_mem	floor;
	cl_mem	ceil;
	cl_mem	door;
}	t_raycast_textures;

typedef struct __attribute__((packed)) s_ray_data
{
	t_v2	ray;
	t_v2	ray_dir;
	float	ray_angle;
	int		side;
	int		door;
}	t_ray_data;

extern t_raycast_textures	g_raycast_textures;
extern t_raycast			g_raycast;

void	raycast_dists(void);
void	raycast_draw(void);
void	minimap_init(void);
#endif