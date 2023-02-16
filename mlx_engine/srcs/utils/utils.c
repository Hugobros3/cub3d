/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 22:02:50 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/24 15:56:37 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine_int.h"
#include "mlx_engine.h"
#include <dlfcn.h>
#include <stdarg.h>

t_color	mlxe_eval_image(t_ui *ui, t_v2 uv)
{
	t_color	color;

	color = sample_texture((t_image *)ui->data, uv);
	color.w = (int)(ft_invlerp(255.0, 1.0, (float)color.w) * 255.0);
	return (color);
}

#ifdef DEBUG

char	*mlxe_get_symbol(void *p)
{
	char	out[8];
	Dl_info	info;

	ft_bzero(&info, sizeof(Dl_info));
	dladdr(p, &info);
	if (info.dli_saddr)
		return (ft_strdup(info.dli_sname));
	ft_atoix((unsigned long)p, out, sizeof(char) * 8);
	return (ft_strdup(out));
}
#else

char	*mlxe_get_symbol(void *p)
{
	char	out[8];

	ft_atoix((unsigned long)p, out, sizeof(char) * 8);
	return (ft_strdup(out));
}
#endif
