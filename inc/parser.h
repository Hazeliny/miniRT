/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:56:30 by mpietrza          #+#    #+#             */
/*   Updated: 2024/11/30 00:12:19 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// parser.c
void    parse(t_rt *rt, const char *file_name);
int check_filename(char *fn);
void 	decode_line(char *line, t_rt *rt);
int	verify_line_elem(char *line);

// parser_decode_figures.c
void	decode_sp(char *line, t_rt *rt);
void	decode_pl(char *line, t_rt *rt);
void	decode_cy(char *line, t_rt *rt);

// parser_decode_unique.c
void	decode_al(char *line, t_rt *rt);
void	decode_cam(char *line, t_rt *rt);
void	decode_lit(char *line, t_rt *rt);

#endif
