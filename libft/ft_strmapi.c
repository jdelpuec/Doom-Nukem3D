/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:47:22 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 16:08:06 by ebonafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	a;
	char			*s2;

	a = 0;
	if (s == 0 || f == 0)
		return (NULL);
	s2 = (char*)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (s2 == 0)
		return (NULL);
	while (s[a])
	{
		s2[a] = f(a, s[a]);
		a++;
	}
	s2[a] = '\0';
	return (s2);
}
