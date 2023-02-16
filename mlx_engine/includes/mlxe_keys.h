/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_keys.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:23:51 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/28 10:36:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXE_KEYS_H
# define MLXE_KEYS_H

# ifdef OSX
#  define KEY_F 3
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_E 12
#  define KEY_Q 14

#  define KEY_O 31
#  define KEY_K 40
#  define KEY_L 37
#  define KEY_M 46
#  define KEY_P 35
#  define KEY_I 34

#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_ESCAPE 53
#  define KEY_SPACE 49
# endif
# ifdef LINUX
#  define KEY_W 122
#  define KEY_F 102
#  define KEY_A 113
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_E 101
#  define KEY_Q 97
#  define KEY_O 111
#  define KEY_K 107
#  define KEY_L 108
#  define KEY_M 109
#  define KEY_P 112
#  define KEY_I 105
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_ESCAPE 65307
#  define KEY_SPACE 32
# endif

#endif