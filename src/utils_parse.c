/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:48:13 by linyao            #+#    #+#             */
/*   Updated: 2024/12/22 13:02:05 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void    check_negative(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == '-' && i != 0)
            terminate(ERR_PARA);
        if (s[0] == '-' && !s[1])
            terminate(ERR_PARA);
        i++;
    }
}

void    check_extreme(char *s)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (s[0] == '-')
        j++;
    while (s[i + j] && s[i + j] != '.')
        i++;
    if (i > 10)
        terminate(ERR_MAX_FLOAT);
}
/*
void    check_float(char *s)
{
    int i;
    int j;
    int dec;

    i = -1;
    j = 0;
    dec = -1;
    while (s[++i])
        if (s[i] == '.')
            j++;
    i = -1;
    while (s[++i])
    {
        if ((i == 0 && s[i] == '.') || (j > 1))
            terminate(ERR_PARA);
        else if (s[i] == '.' && (!ft_isdigit(s[i - 1]) \
                        || !ft_isdigit(s[i + 1])))
            terminate(ERR_PARA);
        else if (s[i] == '.')
            dec = i + 4;
        else if (i == dec)
            terminate(ERR_MAX_FLOAT);
    }
}
*/