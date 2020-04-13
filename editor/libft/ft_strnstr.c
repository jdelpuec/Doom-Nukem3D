/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 16:39:46 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:55:43 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(char const *dest, char const *src, size_t n)
{
	size_t	a;
	size_t	b;
	size_t	c;

	a = 0;
	if (!*src)
		return ((char*)dest);
	while (dest[a] && a < n)
	{
		b = a;
		c = 0;
		while (dest[b] == src[c] && b < n)
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
