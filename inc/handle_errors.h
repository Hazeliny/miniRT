/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:10:38 by linyao            #+#    #+#             */
/*   Updated: 2024/11/29 23:13:58 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_ERRORS_H
# define HANDLE_ERRORS_H

# include <errno.h>

# define ERR_ARGV		"Error: one input argument is mandatory"
# define ERR_MEMO		"Error: memory allocation failed"
# define ERR_RENDER		"Error: ray tracing rendering failed"
# define ERR_FILENAME   "Error: incorrect file type"
# define ERR_OPEN		"Error: file opening failed"
# define ERR_FILEREAD	"Error: file reading failed"
# define ERR_FILE_CONTENT   "Error: incorrect format of rt file"
# define ERR_ID         "Error: incorrect object identifier"
# define ERR_AL			"Error: ambient light decoding failed"
# define ERR_CAM		"Error: camera decoding failed"
# define ERR_LIT		"Error: light decoding failed"
# define ERR_SPH		"Error: sphere decoding failed"
# define ERR_PLN		"Error: plane decoding failed"
# define ERR_CYL		"Error: cylinder decoding failed"

/*==========================		enumerations		======================*/
typedef enum e_err
{
	NO_ERR,
	ERR,
	AL_ERR,
	CAM_ERR,
	LIT_ERR,
	OBJ_ERR,
	SPH_ERR,
	PLN_ERR,
	CYL_ERR
}	t_err;

/*=======================		function definitions		======================*/
// handle_errors.c
void    terminate(char *s);

#endif
