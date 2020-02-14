/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:45:16 by cduverge          #+#    #+#             */
/*   Updated: 2019/07/29 09:36:11 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

static int	get_line(char **line, char **saved, char *next)
{
	if (!(*line = ft_strsub(*saved, 0, next - *saved)))
		return (-1);
	*saved = ft_memmove(*saved, next + 1, ft_strlen(next + 1) + 1);
	return (1);
}

static int	do_last_line(int ret, char **saved, char **line)
{
	if (ret == -1)
		return (-1);
	if (*saved && **saved)
	{
		*line = ft_strdup(*saved);
		free(*saved);
		*saved = NULL;
		return (1);
	}
	return (0);
}

static int	fd_next_line(int fd, char **line, char **saved)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;
	char	*next;
	char	*tmp;

	if (!*saved)
		return (0);
	if ((next = ft_strchr(*saved, '\n')))
		return (get_line(line, saved, next));
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = *saved;
		if (!(*saved = ft_strjoin(*saved, buf)))
			return (-1);
		free(tmp);
		if (ft_strchr(buf, '\n'))
			return (fd_next_line(fd, line, saved));
		*line = *saved;
	}
	return (do_last_line(ret, saved, line));
}

int			get_next_line(const int fd, char **line)
{
	static t_save	*file;
	t_save			*ptr;

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (file)
	{
		ptr = file;
		while (ptr && ptr->fd != fd)
			ptr = ptr->next;
		if (ptr)
			return (fd_next_line(fd, line, &ptr->str));
	}
	if (!(ptr = (t_save *)ft_memalloc(sizeof(t_save))))
		return (-1);
	ptr->fd = fd;
	if (file)
		ptr->next = file;
	else
		ptr->next = NULL;
	file = ptr;
	if (!(ptr->str = (char *)ft_memalloc(sizeof(char))))
		return (-1);
	return (fd_next_line(fd, line, &ptr->str));
}
