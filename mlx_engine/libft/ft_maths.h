/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:43:18 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/18 07:19:51 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATHS_H
# define FT_MATHS_H

# include <stdlib.h>
# include "ft_vectors.h"
# include <math.h>

# define DEG_TO_RAD 0.01745329251
# define RAD_TO_DEG 57.2957795131

//2D cos
t_v2	ft_cos2(t_v2 v);

//3D cos
t_v3	ft_cos3(t_v3 v);

//4D cos
t_v4	ft_cos4(t_v4 v);

//2D sin
t_v2	ft_sin2(t_v2 v);

//3D sin
t_v3	ft_sin3(t_v3 v);

//4D sin
t_v4	ft_sin4(t_v4 v);

//Returns the distance from p to line [s1;s2]
float	ft_dist_line(t_v2 p, t_v2 s1, t_v2 s2);

//Returns a random point on a circle of r=1
t_v2	ft_rand_circle(unsigned int seed);

//Noise
float	ft_noise2(t_v2 st);

//Returns a random float between 1 and 0
float	ft_frand2(t_v2 st);

//Returns a random float between 1 and 0
float	ft_frand(unsigned int n);

//Returns the absolute value of n
int		ft_abs(int n);

//Returns the absolute value of n
float	ft_fabs(float n);

//Wraps n in [min, max]
int		ft_wrap(int n, int min, int max);

//Wraps n in [min, max]
float	ft_fwrap(float x, float min, float max);

//Returns true if number is between the specified range. (Inclusive)
int		ft_isrange(int i, int min, int max);

//Returns the magnitude of n.
size_t	ft_magnitude(long n);

//Check if a number is prime.
int		ft_is_prime(int nb);

//Raises nb to power
int		ft_pow(int nb, int power);

//Returns the smallest between a and b.
int		ft_min(int a, int b);

//Returns the smallest between a and b.
float	ft_fmin(float a, float b);

//Returns the largest between a and b.
int		ft_max(int a, int b);

//Returns the largest between a and b.
float	ft_fmax(float a, float b);

//Lerp
float	ft_lerp(float a, float b, float t);

//Lerp 2D
t_v2	ft_lerp2(t_v2 a, t_v2 b, float t);

//Lerp 3D
t_v3	ft_lerp3(t_v3 v_1, t_v3 v_2, float t);

//Lerp 4D
t_v4	ft_lerp4(t_v4 v_1, t_v4 v_2, float t);

//Inverse lerp
float	ft_invlerp(float min, float max, float v);

//Inverse lerp 2D
t_v2	ft_invlerp2(t_v2 a, t_v2 b, t_v2 t);

//Inverse lerp 3D
t_v3	ft_invlerp3(t_v3 a, t_v3 b, t_v3 t);

//Inverse lerp 4D
t_v4	ft_invlerp4(t_v4 a, t_v4 b, t_v4 t);

//Smooth step
float	ft_smoothstep(float a, float b, float t);

//Smooth step 2D
t_v2	ft_smoothstep2(t_v2 x, t_v2 y, t_v2 s);

//Clamp
int		ft_clamp(int min, int max, int v);

//Clamp for floats
float	ft_clampf(float min, float max, float v);

//Distance between 2 2D points
float	ft_dist2(t_v2 p1, t_v2 p2);

//Distance between 2 2D points raised to the power of 2
float	ft_sqrdist2(t_v2 p1, t_v2 p2);

//Distance between 2 3D points
float	ft_dist3(t_v3 p1, t_v3 p2);

//Distance between 2 3D points raised to the power of 2
float	ft_sqrdist3(t_v3 p1, t_v3 p2);

//Normalizes a 3D vector
t_v3	ft_normalize3(t_v3 v);

//Normalizes a 2D vector
t_v2	ft_normalize2(t_v2 v);

//Dot product of a 2D vector
float	ft_dot2(t_v2 a, t_v2 b);

//Dot product of a 3D vector
float	ft_dot3(t_v3 a, t_v3 b);

//Fractional part of v
float	ft_frac(float v);

//Fractional part of v
t_v2	ft_frac2(t_v2 v);

//Maps v from range [from.x, from.y] to range [to.x, to.y]
float	ft_map(float v, t_v2 from, t_v2 to);

//Rotates a 2D vector around origin
t_v2	ft_rotate2(t_v2 v, float angle, t_v2 origin);

//Converts degrees to radians
float	ft_radians(float degrees);

//Converts radians to degrees
float	ft_degrees(float radians);

#endif