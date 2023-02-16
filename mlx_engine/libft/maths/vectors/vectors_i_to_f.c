/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_i_to_f.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 22:06:56 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/18 06:56:13 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"

inline t_v2	iv2v2(t_iv2 v)
{
	return (v2(v.x, v.y));
}

inline t_v3	iv3v3(t_iv3 v)
{
	return (v3(v.x, v.y, v.z));
}

inline t_v4	iv4v4(t_iv4 v)
{
	return (v4(v.x, v.y, v.z, v.w));
}
