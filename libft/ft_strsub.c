/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:41:34 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:56:03 by lubernar         ###   ########.fr       */
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
