/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:15:43 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:56:28 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/get_next_line.h"

void		ft_free(char **tmp2, char **tmp3, char **tmp4)
{
	free(*tmp2);
	free(*tmp3);
	free(*tmp4);
}

int			check_tmp(char **tmp, char **line)
{
	char	*s;
	int		a;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	a = 0;
	if (!*tmp)
		return (0);
	if ((s = ft_strchr(*tmp, '\n')) != NULL)
	{
		tmp4 = ft_strdup(s + 1);
		tmp3 = ft_strdup(*tmp);
		while (tmp3[a] != '\n' && tmp3[a])
			a++;
		tmp2 = ft_strnew(a);
		*line = ft_strjoin2(*line, ft_strncpy(tmp2, *tmp, a), 1);
		free(*tmp);
		*tmp = ft_strdup(tmp4);
		ft_free(&tmp2, &tmp3, &tmp4);
		return (2);
	}
	*line = ft_strjoin2(*line, *tmp, 2);
	*tmp = NULL;
	return (1);
}

int			check_buf(char *buf, char **tmp, char **line)
{
	char	*s;
	int		a;
	char	*tmp2;
	char	*tmp3;

	a = 0;
	s = NULL;
	if ((s = ft_strchr(buf, '\n')) != NULL)
	{
		tmp3 = ft_strdup(s + 1);
		while (buf[a] != '\n' && buf[a])
			a++;
		tmp2 = ft_strnew(a);
		*line = ft_strjoin2(*line, ft_strncpy(tmp2, buf, a), 1);
		free(tmp2);
		free(*tmp);
		*tmp = ft_strdup(tmp3);
		free(tmp3);
		return (1);
	}
	*line = ft_strjoin2(*line, buf, 1);
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static char	*tmp;
	char		*buf;
	int			ret;
	int			a;

	a = 0;
	if (fd < 0 || BUFF_SIZE < 1 || (void*)line == 0)
		return (-1);
	*line = NULL;
	if ((a = check_tmp(&tmp, line)) == 2)
		return (1);
	buf = ft_strnew(BUFF_SIZE + 1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		a = check_buf(buf, &tmp, line);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	if (tmp || (*line && *line[0]))
		return (1);
	if (ret == -1)
		return (-1);
	return (0);
}
