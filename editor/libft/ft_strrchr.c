/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 15:07:59 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:55:48 by lubernar         ###   ########.fr       */
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
