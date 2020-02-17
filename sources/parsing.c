/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:52:46 by cduverge          #+#    #+#             */
/*   Updated: 2020/02/15 19:01:14 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		data_wall(int fd, t_env *doom, int i)
{
	int		j;

	j = 0;
	while (j < doom->sct[i].wall_count)
	{
		if (check_portal_sector(fd, doom->sct[i].walls, j) == -1)
			return (-1);
		if (check_data_wall(fd, doom, i, j) == -1)
			return (-1);
		++j;
	}
	return (0);
}

void	give_me_data_wall(char *str, t_env *doom, int index)
{
	int		i;

	i = 0;
	doom->sct[index].wall_count = ft_atoi(str + i);
	while (str[i] != ' ')
		++i;
	doom->sct[index].floor_height = ft_atoi(str + i);
	++i;
	while (str[i] != ' ')
		++i;
	doom->sct[index].ceil_height = ft_atoi(str + i);
	++i;
	while (str[i] != ' ')
		++i;
	doom->sct[index].id_floor = ft_atoi(str + i);
	++i;
	while (str[i] != ' ')
		++i;
	doom->sct[index].id_ceil = ft_atoi(str + i);
	++i;
	while (str[i] != ' ')
		++i;
	doom->sct[index].brightness = ft_atof(str + i);
}

int		check_data_sector(int fd, t_env *doom, int index)
{
	char	*line;
	int		ret;

	if ((ret = get_next_line(fd, &line)) > 0)
		if (number_or_dot(line) == -1)
			return (free_and_return(line));
	if (ret == 0)
		return (-1);
	if (check_entire_line(line) == -1)
		return (free_and_return(line));
	give_me_data_wall(line, doom, index);
	free(line);
	if (!(doom->sct[index].walls = (t_wall *)malloc(sizeof(t_wall)
					* doom->sct[index].wall_count)))
		return (-1);
	if (data_wall(fd, doom, index) == -1)
		return (-1);
	return (0);
}

int		all_room(int fd, t_env *doom, int n_room)
{
	if (back_to_line(fd) == -1)
		return (-1);
	if (check_data_sector(fd, doom, n_room) == -1)
		return (-1);
	++n_room;
	if (n_room == doom->room)
	{
		if (back_to_line(fd) == -1)
			return (-1);
		if (get_nb_sprites(fd, doom) == -1)
			return (-1);
		if (check_sprites(fd, doom, 0))
			return (-1);
		return (0);
	}
	return (all_room(fd, doom, n_room));
}

int		parsing(char *str, t_env *doom)
{
	int		fd;
	int		ret;
	char	*line;

	if ((fd = open(str, O_RDONLY)) == -1)
	{
		ft_putendl_fd("File does not exist.", 2);
		return (-1);
	}
	if ((ret = get_next_line(fd, &line)) <= 0)
	{
		ft_putendl_fd("Empty file.", 2);
		return (-1);
	}
	// if ((ft_isdigit(line[0]) == 1) && (line[1] == '\0'))
	// {
		doom->room = ft_atoi(line);
		free(line);
	// }
	// else
		// return (free_and_return(line));
	if (doom->room > 99)
		return (-1);
	if (all_check(doom, fd) == -1)
		return (-1);
	return (0);
}
