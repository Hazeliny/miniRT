/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:40:27 by mpietrza          #+#    #+#             */
/*   Updated: 2024/12/01 19:23:58 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int ft_isspace(char *s)
{
    int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && \
			s[i] != '\v' && s[i] != '\f' && s[i] != '\r')
			return (1);
		i++;
	}
	return (0);
}

t_obj	*find_lstlast(t_obj **obj)
{
	t_obj	*last;

	if (!(*obj))
		return (*obj);
	last = *obj;
	while (last->next)
		last = last->next;
	return (last);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static float	ft_atof_decimal(const char *str, float *decimal)
{
	while (*str >= '0' && *str <= '9')
	{
		*decimal = *decimal * 10 + *str - '0';
		str++;
	}
	return (*decimal);
}

float	ft_atof(const char *str)
{
	float	result;
	float	decimal;
	int		sign;

	result = 0;
	decimal = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	if (*str == '.')
	{
		str++;
		decimal = ft_atof_decimal(str, &decimal);
	}
	return (sign * (result + decimal / pow(10, ft_strlen(str))));
}

