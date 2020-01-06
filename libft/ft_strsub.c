/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:41:34 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 16:12:23 by ebonafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	int		a;

	a = 0;
	if (!*s)
		return (NULL);
	s2 = (char*)malloc(sizeof(char) * len + 1);
	if (s2 == NULL)
		return (NULL);
	while (s[start] != '\0' && len)
	{
		s2[a++] = s[start++];
		len--;
	}
	s2[a] = '\0';
	return (s2);
}
