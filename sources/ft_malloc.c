/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:02:00 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/10 10:52:11 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int				*int_malloc(char *name, int size)
{
	int	*tmp;

	if (!(tmp = (int *)malloc(sizeof(int) * size)))
	{
		ft_putstr("Malloc error : ");
		ft_putendl(name);
		return (NULL);
	}
	return (tmp);
}

char			*string_malloc(char *name, int size)
{
	char	*tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * size)))
	{
		ft_putstr("Malloc error : ");
		ft_putendl(name);
		return (NULL);
	}
	return (tmp);
}

char			**tab_malloc(char *name, int size)
{
	char	**tmp;

	if (!(tmp = (char **)malloc(sizeof(char *) * size)))
	{
		ft_putstr("Malloc error : ");
		ft_putendl(name);
		return (NULL);
	}
	return (tmp);
}

unsigned char	*unsigned_char_malloc(char *name, int size)
{
	unsigned char	*tmp;

	if (!(tmp = (unsigned char *)malloc(sizeof(unsigned char) * size)))
	{
		ft_putstr("Malloc error : ");
		ft_putendl(name);
		return (NULL);
	}
	return (tmp);
}
