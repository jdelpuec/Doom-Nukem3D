/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:12:50 by cduverge          #+#    #+#             */
/*   Updated: 2019/12/16 18:38:05 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Doom.h"

int		main(int ac, char **av)
{
	t_env	doom;

	if (ac > 2)
	{
		ft_putendl_fd(USAGE, 2);
		return (-1);
	}
	if (parsing(av[1], &doom) == -1)
	{
		ft_putendl_fd(USAGE, 2);
		return (-1);
	}
	//debut test d affichage
#include <stdio.h>
	printf("%f\n", doom.sct[5].walls[1].x1);
	printf("%f\n", doom.sct[5].walls[1].y1);
	printf("%f\n", doom.sct[5].walls[1].x2);
	printf("%f\n", doom.sct[5].walls[1].y2);
//	while (1)
//		;
	//fin test d affichage
return (0);
}