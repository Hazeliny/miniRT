/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:40:27 by linyao            #+#    #+#             */
/*   Updated: 2024/12/18 23:21:29 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int ft_isspace_str(char *s)
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

t_cam	*find_lstlast_cam(t_cam **cam)
{
	t_cam	*last;

	if (!(*cam))
		return (*cam);
	last = *cam;
	while (last->next)
		last = last->next;
	return (last);
}

t_lit	*find_lstlast_lit(t_lit **lit)
{
	t_lit	*last;

	if (!(*lit))
		return (*lit);
	last = *lit;
	while (last->next)
		last = last->next;
	return (last);
}

t_obj	*find_lstlast_obj(t_obj **obj)
{
	t_obj	*last;

	if (!(*obj))
		return (*obj);
	last = *obj;
	while (last->next)
		last = last->next;
	return (last);
}

void	*ft_calloc_new(size_t num, size_t size)
{
	size_t	total_size;
	void	*ptr;

	total_size = num * size;
	ptr = malloc(total_size);
	if (!ptr)
		terminate("ERROR_MEMO");
	ft_memset(ptr, 0, total_size);
	return (ptr);
}