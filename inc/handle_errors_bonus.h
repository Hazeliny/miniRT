/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:10:38 by linyao            #+#    #+#             */
/*   Updated: 2025/01/10 12:39:03 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_ERRORS_BONUS_H
# define HANDLE_ERRORS_BONUS_H

# include <errno.h>

# define ERR_ARGV		"Error: incorrect number of arguments"
# define ERR_MEMO		"Error: memory allocation failed"
# define ERR_RENDER		"Error: ray tracing rendering failed"
# define ERR_FILENAME   "Error: incorrect file type"
# define ERR_OPEN		"Error: file opening failed"
# define ERR_FILEREAD	"Error: file reading failed"
# define ERR_FILE_CONTENT   "Error: incorrect format of rt file"
# define ERR_ID         "Error: incorrect object identifier"
# define ERR_PARA       "Error: incorrect parameter"
# define ERR_MAX_FLOAT  "Error: maximum 3 decimals exceeded"
# define ERR_AL			"Error: incorrect number of ambient light"
# define ERR_ACL        "Error: al, cam, or light cannot be empty"

/*==================		function definitions		=================*/

void	terminate(char *s);

#endif
