/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 15:33:12 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 16:12:10 by ebonafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strstr(char const *dest, char const *src)
{
	int a;
	int	b;
	int c;

	a = 0;
	if (!*src)
		return ((char*)dest);
	while (dest[a])
	{
		b = a;
		c = 0;
		while (dest[b] == src[c])
		{
			b++;
			c++;
			if (src[c] == '\0')
				return ((char*)(&dest[a]));
		}
		a++;
	}
	return (NULL);
}
