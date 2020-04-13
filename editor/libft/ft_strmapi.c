/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:47:22 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:55:19 by lubernar         ###   ########.fr       */
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
