/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwarin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:43:37 by siwarin           #+#    #+#             */
/*   Updated: 2018/11/29 12:35:36 by siwarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define BUF 80

int		ft_display_file(char *str)
{
	int		fd;
	int		ret;
	char	tab[BUF + 1];

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (-1);
	while ((ret = read(fd, tab, BUF)))
	{
		tab[ret] = '\0';
		ft_putstr(tab);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int i;

	i = 1;
	if (argc < 2)
		ft_putstr("File name missing.\n");
	while (i != argc)
	{
		ft_display_file(argv[i]);
		i++;
	}
	return (0);
}
