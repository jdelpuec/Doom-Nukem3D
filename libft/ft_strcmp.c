/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 13:01:32 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/28 22:12:23 by ebonafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_strcmp(char const *s1, char const *s2)
{
	int a;
	int b;

	a = 0;
	b = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (s1[a] || s2[b])
	{
		if ((s1[a] - s2[b]) != 0)
			return ((unsigned char)s1[a] - (unsigned char)s2[b]);
		a++;
		b++;
	}
	return (0);
}
