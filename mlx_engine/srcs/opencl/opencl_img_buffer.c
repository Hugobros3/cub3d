/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_img_buffer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 23:36:25 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/30 18:39:14 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxcl.h"

static cl_image_desc	make_image_desc(t_image *img)
{
	cl_image_desc	image_desc;

	image_desc.image_type = CL_MEM_OBJECT_IMAGE2D;
	image_desc.image_width = img->size->x;
	image_desc.image_height = img->size->y;
	image_desc.image_depth = 0;
	image_desc.image_array_size = 0;
	image_desc.image_row_pitch = 0;
	image_desc.image_slice_pitch = 0;
	image_desc.num_mip_levels = 0;
	image_desc.num_samples = 0;
	image_desc.buffer = NULL;
	return (image_desc);
}

static cl_image_format	make_format(void)
{
	cl_image_format	format;

	format.image_channel_order = CL_R;
	format.image_channel_data_type = CL_SIGNED_INT32;
	return (format);
}

static cl_mem	make_buffer(t_mlxcl_data *mlxcl, t_image *img)
{
	cl_mem			img_buf;
	cl_int			err;
	cl_image_format	format;
	cl_image_desc	image_desc;

	format = make_format();
	image_desc = make_image_desc(img);
	img_buf = clCreateImage(mlxcl->context, CL_MEM_READ_ONLY,
			&format, &image_desc, NULL, &err);
	mlxcl_check_err(err, "Couldn't create image buffer\n");
	return (img_buf);
}

cl_mem	mlxcl_create_img_buffer(t_mlxcl_data *mlxcl, t_image *img)
{
	cl_mem			img_buf;
	cl_int			err;
	size_t			origin[3];
	size_t			region[3];

	ft_bzero(origin, sizeof(origin));
	region[0] = img->size->x;
	region[1] = img->size->y;
	region[2] = 1;
	img_buf = make_buffer(mlxcl, img);
	err = clEnqueueWriteImage(mlxcl->queue, img_buf, CL_TRUE,
			origin,
			region,
			0, 0, img->addr, 0, NULL, NULL);
	mlxcl_check_err(err, "Couldn't write image to buffer\n");
	return (img_buf);
}
