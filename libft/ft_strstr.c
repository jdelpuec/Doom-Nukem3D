/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 15:33:12 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:55:59 by lubernar         ###   ########.fr       */
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
