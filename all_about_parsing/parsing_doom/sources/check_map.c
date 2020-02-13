/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:57:37 by cduverge          #+#    #+#             */
/*   Updated: 2020/02/13 12:05:28 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Doom.h"

int		check_room_by_room(t_env *d, int j)
{
	int		i;
	float	a;
	float	b;

	i = 0;
	a = d->sct[j].walls[i].p1.x;
	b = d->sct[j].walls[i].p1.y;
	while (i < d->sct[j].wall_count)
	{
		if (((i + 1) < d->sct[j].wall_count)
				&& ((d->sct[j].walls[i].p2.x == d->sct[j].walls[i + 1].p1.x)
				&& (d->sct[j].walls[i].p2.y == d->sct[j].walls[i + 1].p1.y)))
			++i;
		else if ((i >= 2) && ((a == d->sct[j].walls[i].p2.x)
					&& (b == d->sct[j].walls[i].p2.y)))
			++i;
		else
			return (-1);
	}
	if (i != d->sct[j].wall_count)
		return (-1);
	return (0);
}

int		free_and_return(char *str)
{
	free(str);
	return (-1);
}

int		begin_player(int fd, t_env *doom)
{
	char	*line;
	int		ret;

	if (back_to_line(fd) == -1)
		return (-1);
	if ((ret = get_next_line(fd, &line)))
	{
		if (number_or_dot(line) == -1)
			return (free_and_return(line));
		if (check_player(line) == -1)
			return (free_and_return(line));
		fill_up_player(line, doom);
	}
	free(line);
	return (0);
}

int		check_player(char *line)
{
	int		i;
	int		spc;

	i = 0;
	spc = 0;
	while ((line[i] != '\0') && (spc < 3))
	{
		if ((i = body_of_check_line(line, i)) == -1)
			return (-1);
		if (line[i] == ' ')
		{
			++i;
			++spc;
		}
	}
	if ((ft_isdigit(line[i]) == 1) && (line[i + 1] == '\0'))
		return (0);
	else
		return (-1);
}
