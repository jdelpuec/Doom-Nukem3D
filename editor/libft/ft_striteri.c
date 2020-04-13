/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:32:48 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:54:50 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;
	int				a;

	a = 0;
	i = 0;
	if (s == NULL || f == NULL)
		return ;
	while (s[a])
	{
		f(i, s + a);
		i++;
		a++;
	}
}
