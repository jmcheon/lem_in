/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 02:39:00 by sucho             #+#    #+#             */
/*   Updated: 2022/09/13 00:27:31 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*gnl_read_line(int fd, char *backup)
{
	char	*buf;
	int		read_bytes;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	read_bytes = 1;
	while (!gnl_strchr(backup, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_bytes] = '\0';
		backup = gnl_strjoin(backup, buf);
	}
	free(buf);
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*backup[256];

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (0);
	backup[fd] = gnl_read_line(fd, backup[fd]);
	if (!backup[fd])
		return (NULL);
	line = gnl_get_line(backup[fd]);
	backup[fd] = gnl_new_backup(backup[fd]);
	return (line);
}
