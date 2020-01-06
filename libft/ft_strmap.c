/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:42:19 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 16:07:57 by ebonafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*s2;
	int		a;

	a = 0;
	if (f == 0 || s == 0)
		return (NULL);
	s2 = (char*)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (s2 == 0)
		return (NULL);
	while (s[a])
	{
		s2[a] = f(s[a]);
		a++;
	}
	s2[a] = '\0';
	return (s2);
}
