/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:10:38 by linyao            #+#    #+#             */
/*   Updated: 2024/11/25 14:59:43 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_ERRORS_H
# define HANDLE_ERRORS_H

# include <errno.h>

# define ERR_ARGV		"Error: one input argument is mandatory"
# define ERR_MEMO		"Error: memory allocation failed"
# define ERR_RENDER		"Error: ray tracing rendering failed"

void    terminate(char *s);

#endif