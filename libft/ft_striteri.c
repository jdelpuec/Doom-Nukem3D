/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:32:48 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 16:06:42 by ebonafi          ###   ########.fr       */
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
