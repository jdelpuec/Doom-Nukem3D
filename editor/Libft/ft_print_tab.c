/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwarin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 18:57:52 by siwarin           #+#    #+#             */
/*   Updated: 2019/01/21 17:59:59 by siwarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_tab(int **tab, int tab_sizey, int tab_sizex)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < tab_sizey)
	{
		while (x < tab_sizex)
		{
			ft_putchar(tab[x][y] + 48);
			x++;
		}
		ft_putchar('\n');
		x = 0;
		y++;
	}
}
