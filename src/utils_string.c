/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:40:27 by mpietrza          #+#    #+#             */
/*   Updated: 2024/11/25 15:40:33 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

size_t	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && dst[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}
static double	ft_atof_decimal(const char *str, double *decimal)
{
	while (*str >= '0' && *str <= '9')
	{
		*decimal = *decimal * 10 + *str - '0';
		str++;
	}
	return (*decimal);
}

double	ft_atof(const char *str)
{
	double	result;
	double	decimal;
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
