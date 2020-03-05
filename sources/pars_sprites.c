/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:39:40 by cduverge          #+#    #+#             */
/*   Updated: 2020/03/05 14:40:21 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		check_sprites(int fd, t_env *doom, int nb)
{
	char	*line;
	int		ret;

	if (back_to_line(fd) == -1)
		return (-1);
	if ((ret = get_next_line(fd, &line)) > 0)
	{
		if (number_or_dot(line) == -1)
			return (free_and_return(line));
		if (check_line(line) == -1)
			return (free_and_return(line));
		fill_up_sprite_coor(line, doom, nb);
		free(line);
	}
	if (ret <= 0)
		return (-1);
	if (check_sprite_id(fd, doom, nb) == -1)
		return (-1);
	++nb;
	if (nb == doom->sprites)
		return (0);
	return (check_sprites(fd, doom, nb));
}

int		get_nb_sprites(int fd, t_env *doom)
{
	int		ret;
	char	*line;

	if ((ret = get_next_line(fd, &line)) > 0)
	{
		doom->sprites = ft_atoi(line);
		free(line);
		if (doom->sprites < 1 || doom->sprites > 20)
			return (-1);
		if (!(doom->spt = malloc(sizeof(t_sprites) * doom->sprites)))
			return (-1);
	}
	if (ret <= 0)
		return (-1);
	return (0);
}

void	fill_up_sprite_coor(char *str, t_env *doom, int i)
{
	int		k;

	k = 0;
	doom->spt[i].pos.x = ft_atof(str + k);
	while (str[k] != ' ')
		++k;
	doom->spt[i].pos.y = ft_atof(str + k);
	++k;
	while (str[k] != ' ')
		++k;
	doom->spt[i].pos.z = ft_atof(str + k);
}

int		check_sprite_id(int fd, t_env *doom, int i)
{
	char	*line;
	int		ret;
	int		k;

	k = 0;
	if ((ret = get_next_line(fd, &line)) > 0)
	{
		if (number_or_dot(line) == -1)
			return (free_and_return(line));
		while (line[k] != '\0')
		{
			if (check_sprite_id_2(line, doom, i) == -1)
				return (-1);
			while (line[k] != ' ' && line[k] != '\0')
				++k;
			++k;
			doom->spt[i].sector = ft_atoi(line + k);
			if (doom->spt[i].sector < 0)
				return (free_and_return(line));
		}
		free(line);
	}
	if (ret <= 0)
		return (-1);
	return (0);
}

int		check_if_sprites(int fd)
{
	int		ret;
	char	*line;
	int		i;

	i = 0;
	while (i < 3)
	{
		ret = get_next_line(fd, &line);
		if (ret == 0)
			return (0);
		else if (ret == -1)
			return (-1);
		free(line);
		++i;
	}
	return (2);
}
