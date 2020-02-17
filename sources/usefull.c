/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:25:42 by cduverge          #+#    #+#             */
/*   Updated: 2020/02/15 17:11:01 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

float	ft_atof(char *s)
{
	float			 res;
	int				signe;
	unsigned long	i;

	res = 0.f;
	signe = 1;
	i = 0;
	if (s)
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (s[i] == '+' || s[i] == '-')
		{
			if (s[i++] == '-')
				signe = -1;
		}
		res = ft_end_atof(s, i, res);
	}
	if (signe == -1)
		res = -res;
	return (res);
}

int		check_line(char *str)
{
	int		i;
	int		spc;

	spc = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((i = body_of_check_line(str, i)) == -1)
			return (-1);
		if (str[i] == ' ')
		{
			++i;
			++spc;
		}
		if (spc > 4)
			return (-1);
	}
	return (0);
}

int		check_entire_line(char *str)
{
	int		i;
	int		spc;
	int		lmt;

	spc = 0;
	i = 0;
	lmt = ft_strlen(str);
	while (i < lmt)
	{
		if ((i = check_bright(i, str, spc)) == -1)
			return (-1);
		++spc;
		if (spc > 6)
			return (-1);
	}
	return (0);
}

int		number_or_dot(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '.'
					|| str[i] == ' ' || str[i] == '-'))
			return (-1);
		++i;
	}
	return (0);
}

int		back_to_line(int fd)
{
	char	*line;
	int		x;
	int		ret;

	x = 0;
	while (++x <= 3)
	{
		if ((ret = get_next_line(fd, &line)) > 0)
		{
			if (ft_strcmp(line, "\0") != 0)
				return (free_and_return(line));
			free(line);
		}
		if (ret == 0)
			return (-1);
	}
	return (0);
}
