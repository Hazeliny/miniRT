/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:40:22 by anguil-l          #+#    #+#             */
/*   Updated: 2025/01/04 21:40:51 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

void    check_point(char *s)
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

static int count_commas(char *s)
{
    int i = 0;
    int count = 0;

    while (s[i])
    {
        if (s[i] == ',')
            count++;
        else if (!ft_isdigit(s[i]) && s[i] != '-' && s[i] != '.')
            return (-1);
        i++;
    }
    return (count);
}

static int check_components(char **arr)
{
    int i = 0;
    int j;

    while (arr[i])
    {
        j = 0;
        while (arr[i][j])
        {
            if (!ft_isdigit(arr[i][j]) && arr[i][j] != '-' && arr[i][j] != '.')
                return (0);
            j++;
        }
        i++;
    }
    return (i == 3);
}

void check_commas(char *s)
{
    char **components;
    int commas;

    commas = count_commas(s);
    if (commas != 2 || commas == -1)
        terminate(ERR_PARA);
    components = ft_split(s, ',');
    if (!components || !check_components(components))
    {
        free_array(components);
        terminate(ERR_PARA);
    }
    free_array(components);
}