/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:48:13 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 16:52:23 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

void	check_negative(char *s)
{
	int	i;

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

void	check_extreme(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s[0] == '-')
		j++;
	while (s[i + j] && s[i + j] != '.')
		i++;
	if (i > 10)
		terminate(ERR_MAX_FLOAT);
}

t_vec3	normalize_axis(t_cn *cn)
{
	t_vec3	new;
	t_vec3	expected;
	t_vec3	tmp;

	new = cn->axis;
	normalize(&new);
	tmp = vec3_sum(cn->apex, vec3_mpl(new, cn->hgt));
	expected = vec3_sub(&cn->apex, &tmp);
	if (vec3_dot(&new, &expected) < 0)
		new = vec3_mpl(new, -1);
	return (new);
}
