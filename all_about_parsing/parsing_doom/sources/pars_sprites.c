/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:39:40 by cduverge          #+#    #+#             */
/*   Updated: 2020/02/14 12:07:15 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Doom.h"

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
		if (check_line_sprite(line) == -1)
			return (free_and_return(line));
		fill_up_sprite(line, doom, nb);
		free(line);
	}
	if (ret <= 0)
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

void	fill_up_sprite(char *str, t_env *doom, int i)
{
	int		k;

	k = 0;
	doom->spt[i].pos.x = ft_atof(str + k);
	while (str[k] != ' ')
		++k;
	doom->spt[i].pos.y = ft_atof(str + k);
	while (str[k] != ' ')
		++k;
	doom->spt[i].pos.z = ft_atof(str + k);
	while (str[k] != ' ')
		++k;
	doom->spt[i].id = ft_atoi(str + k);
	while (str[k] != ' ')
		++k;
	doom->spt[i].sector = ft_atoi(str + k);
}

int		check_line_sprite_2(char *str, int k)
{
	int		test;

	test = 0;
	while (str[k] != '\0')
	{
		test = ft_atoi(str + k);
		if (test < 0)
			return (-1);
		while (ft_isdigit(str[k]) == 1)
			++k;
		++k;
	}
	return (0);
}

int		check_line_sprite(char *str)
{
	float	test;
	int		k;
	int		count;

	k = 0;
	count = 0;
	while (++count <= 3)
	{
		test = ft_atof(str + k);
		if (test < -99.9 || test > 99.9)
			return (-1);
		if (test >= 0)
			k = k + 3;
		else
			k = k + 4;
		if (str[k] != ' ')
			return (-1);
		++k;
	}
	if (check_line_sprite_2(str, k) == -1)
		return (-1);
	return (0);
}
