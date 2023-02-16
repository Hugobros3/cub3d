/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:35:17 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/18 07:16:45 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTORS_H
# define FT_VECTORS_H

typedef struct s_iv2
{
	int	x;
	int	y;
}				t_iv2;

typedef struct s_v2
{
	float	x;
	float	y;
}				t_v2;

typedef struct s_iv3
{
	int	x;
	int	y;
	int	z;
}				t_iv3;

typedef struct s_v3
{
	float	x;
	float	y;
	float	z;
}				t_v3;

typedef struct s_iv4
{
	int	x;
	int	y;
	int	z;
	int	w;
}				t_iv4;

typedef struct s_v4
{
	float	x;
	float	y;
	float	z;
	float	w;
}				t_v4;

t_iv2	iv2(int x, int y);
t_v2	v2(float x, float y);

t_iv3	iv3(int x, int y, int z);
t_v3	v3(float x, float y, float z);

t_iv4	iv4(int x, int y, int z, int w);
t_v4	v4(float x, float y, float z, float w);

t_iv2	*piv2(int x, int y);
t_v2	*pv2(float x, float y);

t_iv3	*piv3(int x, int y, int z);
t_v3	*pv3(float x, float y, float z);

t_iv4	*piv4(int x, int y, int z, int w);
t_v4	*pv4(float x, float y, float z, float w);

t_v2	iv2v2(t_iv2 v);
t_v3	iv3v3(t_iv3 v);
t_v4	iv4v4(t_iv4 v);

t_iv2	v2iv2(t_v2 v);
t_iv3	v3iv3(t_v3 v);
t_iv4	v4iv4(t_v4 v);

t_iv2	add2i(t_iv2 a, t_iv2 b);
t_iv3	add3i(t_iv3 a, t_iv3 b);
t_iv4	add4i(t_iv4 a, t_iv4 b);
t_v2	add2(t_v2 a, t_v2 b);
t_v3	add3(t_v3 a, t_v3 b);
t_v4	add4(t_v4 a, t_v4 b);

t_iv2	sub2i(t_iv2 a, t_iv2 b);
t_iv3	sub3i(t_iv3 a, t_iv3 b);
t_iv4	sub4i(t_iv4 a, t_iv4 b);
t_v2	sub2(t_v2 a, t_v2 b);
t_v3	sub3(t_v3 a, t_v3 b);
t_v4	sub4(t_v4 a, t_v4 b);

t_iv2	mult2i(t_iv2 a, t_iv2 b);
t_iv3	mult3i(t_iv3 a, t_iv3 b);
t_iv4	mult4i(t_iv4 a, t_iv4 b);
t_v2	mult2(t_v2 a, t_v2 b);
t_v3	mult3(t_v3 a, t_v3 b);
t_v4	mult4(t_v4 a, t_v4 b);

t_iv2	div2i(t_iv2 a, t_iv2 b);
t_iv3	div3i(t_iv3 a, t_iv3 b);
t_iv4	div4i(t_iv4 a, t_iv4 b);
t_v2	div2(t_v2 a, t_v2 b);
t_v3	div3(t_v3 a, t_v3 b);
t_v4	div4(t_v4 a, t_v4 b);

t_iv2	mod2i(t_iv2 v1, t_iv2 v2);
t_iv3	mod3i(t_iv3 v1, t_iv3 v2);
t_iv4	mod4i(t_iv4 v1, t_iv4 v2);

int		vlen2i(t_iv2 a);
float	vlen2(t_v2 a);

#endif