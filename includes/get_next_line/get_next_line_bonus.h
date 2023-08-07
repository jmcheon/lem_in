/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 02:39:17 by sucho             #+#    #+#             */
/*   Updated: 2023/08/07 07:29:08 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

/*
** get_next_line.c
*/

char	*get_next_line(int fd);

/*
** get_next_line_utils.c
*/

size_t	gnl_strlen(char *s);
char	*gnl_strchr(char *s, int c);
char	*gnl_strjoin(char *backup, char *buf);
char	*gnl_get_line(char *backup);
char	*gnl_new_backup(char *backup);

#endif
