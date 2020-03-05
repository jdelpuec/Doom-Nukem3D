/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:12:50 by cduverge          #+#    #+#             */
/*   Updated: 2020/03/05 14:40:32 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		check_sprite_id_2(char *line, t_env *doom, int i)
{
	doom->spt[i].id = ft_atoi(line);
	if (doom->spt[i].id < 0)
		return (free_and_return(line));
	if (doom->spt[i].id == 1 || doom->spt[i].id == 2)
		doom->spt[i].pickable = 1;
	else
		doom->spt[i].pickable = 0;
	return (0);
}

int		check_bright(int i, char *str, int spc)
{
	float	test;

	test = 0.0;
	if (spc == 5)
	{
		test = ft_atof(str + i);
		if (test < 0 || test > 1)
			return (-1);
		i = i + 3;
	}
	else
	{
		if (ft_isdigit(str[i]) == 0)
			return (-1);
		++i;
		if (str[i] == ' ')
			++i;
		else if (ft_isdigit(str[i]) == 1 && (str[i + 1] == ' '))
			i = i + 2;
		else
			return (-1);
	}
	return (i);
}

int		all_check(t_env *doom, int fd)
{
	if (begin_player(fd, doom) == -1)
		return (-1);
	if (!(doom->sct = malloc(sizeof(t_sector) * doom->room)))
		return (-1);
	if (all_room(fd, doom, 0) == -1)
		return (-1);
	if (close(fd) == -1)
		return (-1);
	if (check_validity_map(doom) == -1)
		return (-1);
	return (0);
}

void	fill_up_player(char *line, t_env *doom)
{
	int		k;

	k = 0;
	doom->player.position.x = ft_atof(line + k);
	while (line[k] != ' ')
		++k;
	doom->player.position.y = ft_atof(line + k);
	++k;
	while (line[k] != ' ')
		++k;
	doom->player.position.z = ft_atof(line + k) + PLAY_H;
	++k;
	while (line[k] != ' ')
		++k;
	doom->player.sector = ft_atoi(line + k);
	++k;
	while (line[k] != ' ')
		++k;
	doom->player.gravity = ft_atoi(line + k);
}

int		check_portal_sector(int fd, t_wall *walls, int j)
{
	char	*line;
	int		ret;

	if ((ret = get_next_line(fd, &line)) > 0)
	{
		if (number_or_dot(line) != -1)
		{
			walls[j].id_text = ft_atoi(line);
			if (walls[j].id_text < 0)
				return (free_and_return(line));
			walls[j].portal_sector = ft_atoi(line + 2);
			if (walls[j].portal_sector < -1)
				return (free_and_return(line));
			free(line);
		}
		else
			return (free_and_return(line));
	}
	if (ret == 0)
		return (-1);
	return (0);
}
