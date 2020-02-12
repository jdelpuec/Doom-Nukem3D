/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 12:36:07 by cduverge          #+#    #+#             */
/*   Updated: 2020/02/12 17:38:01 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Doom.h"

int		check_validity_map(t_env *doom)
{
	int		j;

	j = 0;
	while (j < doom->room)
	{
		if (doom->sct[j].wall_count < 3)
			return (-1);
		if (check_room_by_room(doom, j) == -1)
			return (-1);
		++j;
	}
	return (0);
}

int		body_of_check_line(char *str, int i)
{
	int		count;

	count = 0;
	if (str[i] == '-')
		++i;
	if (ft_isdigit(str[i]) == 0)
		return (-1);
	while (ft_isdigit(str[i]) == 1)
	{
		++i;
		++count;
	}
	if (count > 2 || str[i] != '.')
		return (-1);
	++i;
	if (ft_isdigit(str[i]) == 0)
		return (-1);
	++i;
	return (i);
}

float	ft_end_atof(char *s, unsigned long i, float res)
{
	unsigned long	dec;

	dec = 1;
	while (ft_isdigit(s[i]))
	{
		res *= 10;
		res += (int)(s[i++] - '0');
	}
	if (s[i] == ',' || s[i] == '.')
	{
		i++;
		while (ft_isdigit(s[i]))
		{
			dec *= 10;
			res += (float)(s[i++] - '0') / (float)dec;
		}
	}
	return (res);
}

void	fill_up_sector(char *str, t_env *doom, int i, int j)
{
	int		k;

	k = 0;
	doom->sct[i].walls[j].p1.x = ft_atof(str + k);
	while (str[k] != ' ')
		++k;
	doom->sct[i].walls[j].p1.y = ft_atof(str + k);
	++k;
	while (str[k] != ' ')
		++k;
	doom->sct[i].walls[j].p2.x = ft_atof(str + k);
	++k;
	while (str[k] != ' ')
		++k;
	doom->sct[i].walls[j].p2.y = ft_atof(str + k);
}

int		check_data_wall(int fd, t_env *doom, int i, int j)
{
	int		ret;
	char	*line;

	if ((ret = get_next_line(fd, &line)))
	{
		if (number_or_dot(line) == -1)
			return (free_and_return(line));
		if (check_line(line) == -1)
			return (free_and_return(line));
		fill_up_sector(line, doom, i, j);
		free(line);
	}
	if (ret == -1)
		return (-1);
	return (0);
}
