/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:27:47 by linyao            #+#    #+#             */
/*   Updated: 2025/01/10 13:43:47 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <float.h>
#include <stdio.h>
#include "libft.h"

/*
double	ft_atof(const char *str)
{
	double	result;

	result = 0.0;
	if (!str)
		return (0.0);
	result = atof(str);
	return (result);
}
*/

static int skip_whitespace_and_sign(const char **str)
{
	int	sign;

	sign = 1;
	while (isspace(**str))
		(*str)++;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-') 
			sign = -1;
		else
			sign = 1;
        (*str)++;
    }
	return (sign);
}

static double	parse_fractional_part(const char **str)
{
	double	fraction;
	double	divisor;

    fraction = 0.0;
    divisor = 1.0;
    if (**str == '.')
	{
		(*str)++;
		while (ft_isdigit(**str))
		{
			fraction = fraction * 10.0 + (**str - '0');
			divisor *= 10.0;
			(*str)++;
		}
	}
	return (fraction / divisor);
}

static int	parse_exponent(const char **str)
{
	int	exp_sign;
	int	exponent;

	exp_sign = 1;
	exponent = 0;
	if (**str == 'e' || **str == 'E')
	{
		(*str)++;
		if (**str == '+' || **str == '-')
		{
			if (**str == '-')
				exp_sign = -1;
			else
				exp_sign = 1;
			(*str)++;
        }
		while (ft_isdigit(**str))
		{
			exponent = exponent * 10 + (**str - '0');
			(*str)++;
		}
	}
	return (exp_sign * exponent);
}

static double	handle_overflow(double result, int sign)
{
	if (result > DBL_MAX)
	{
		if (sign == 1)
			return (INFINITY);
		else
			return (-INFINITY);
	}
	if (result < -DBL_MAX)
		return (-INFINITY);
	return (result);
}

double	ft_atof(const char *str)
{
	double	result;
	int		sign;
	int		exponent;

	result = 0.0;
	if (!str)
		return (0.0);
	sign = skip_whitespace_and_sign(&str);
	while (ft_isdigit(*str))
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	result += parse_fractional_part(&str);
	exponent = parse_exponent(&str);
	result *= pow(10.0, exponent);
	result = handle_overflow(result, sign);
	return (result * sign);
}
/*
int main()
{
    printf("%f\n", ft_atof("123.456"));        // 正常输入
    printf("standard: %f\n", atof("123.456"));
    printf("%f\n", ft_atof("-123.456"));       // 负数输入
    printf("standard: %f\n", atof("-123.456"));
    printf("%f\n", ft_atof("1.23e3"));         // 科学计数法
    printf("standard: %f\n", atof("1.23e3"));
    printf("%f\n", ft_atof("-1.23E-3"));//-0.000001  standard: -0.001230
    printf("standard: %f\n", atof("-1.23E-3"));
    printf("%f\n", ft_atof("  +0.00123  "));   // 空格和正号
    printf("standard: %f\n", atof("  +0.00123  ")); 
    printf("%f\n", ft_atof("1e309"));          // 溢出
    printf("standard: %f\n", atof("1e309"));
    printf("%f\n", ft_atof("1e-324"));         // 下溢
    printf("standard: %f\n", atof("1e-324"));
    printf("%f\n", ft_atof(""));               // 空字符串
    printf("standard: %f\n", atof(""));
    printf("NULL %f\n", ft_atof(NULL));             // NULL
//    printf("standard: %f\n", atof(NULL));
    printf("%f\n", ft_atof("abc123"));         // 无效输入
    printf("standard: %f\n", atof("abc123"));
    printf("%f\n", ft_atof("123abc"));         // 混合输入
    printf("standard: %f\n", atof("123abc"));
    printf("%f\n", ft_atof("1e+308"));         // 极端大值 inf
    printf("standard: %f\n", atof("1e+308"));
    return 0;
}
*/
