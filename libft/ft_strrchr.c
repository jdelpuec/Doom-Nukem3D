/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 15:07:59 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 16:11:02 by ebonafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strrchr(char const *s, int c)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	while (s[a])
	{
		if (s[a] == (unsigned char)c)
			b = a;
		a++;
	}
	if (c == 0)
		return ((char*)&s[a]);
	if (((b == 0 && s[b] == (unsigned char)c) || b > 0))
		return ((char*)&s[b]);
	else
		return (NULL);
}
