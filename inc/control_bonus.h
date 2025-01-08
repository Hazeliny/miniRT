/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:37:51 by linyao            #+#    #+#             */
/*   Updated: 2024/12/26 16:25:01 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROL_H
# define CONTROL_H

// mouse buttons
# define M_LEFT 1
# define M_RIGHT 3
# define M_MIDDLE 2
# define M_ROLL_UP 4
# define M_ROLL_DOWN 5

//keys
# ifdef __APPLE__
#  define KEY_ESC 53
#  define KEY_Q 12
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_C 8
#  define KEY_V 9
#  define KEY_LEFT 123
#  define KEY_RIGHT	124
#  define KEY_DOWN	125
#  define KEY_UP	126
#  define KeyPress 2
#  define KeyPressMask (1L<<0)
#  define DestroyNotify 17
#  define StructureNotifyMask (1L<<17)
# else
#  define M_PI 3.14159265358979323846
#  define KEY_ESC	65307
#  define KEY_1		49
#  define KEY_2		50
#  define KEY_3		51
#  define KEY_4		52
#  define KEY_5		53
#  define KEY_6		54
#  define KEY_7		55
#  define KEY_8		56
#  define KEY_9		57
#  define KEY_SUM	65451
#  define KEY_RES	65293
#  define KEY_SUM2	61
#  define KEY_RES2	32
#  define KEY_A		97
#  define KEY_S		115
#  define KEY_D		100
#  define KEY_F		102
#  define KEY_H		104
#  define KEY_G		103
#  define KEY_Z		122
#  define KEY_X		120
#  define KEY_C		99
#  define KEY_V		118
#  define KEY_B		98
#  define KEY_Q		113
#  define KEY_W		119
#  define KEY_E		101
#  define KEY_R		114
#  define KEY_Y		121
#  define KEY_T		116
#  define KEY_U		117
#  define KEY_I		105
#  define KEY_P		112
#  define KEY_L		108
#  define KEY_J		106
#  define KEY_K		107
#  define KEY_N		110
#  define KEY_M		109
#  define KEY_TAB	65289
#  define KEY_LEFT	65361
#  define KEY_RIGHT	65363
#  define KEY_DOWN	65364
#  define KEY_UP		65362
#  define KEY_CTRL	65507
#  define KEY_CMD	105
# endif

#endif