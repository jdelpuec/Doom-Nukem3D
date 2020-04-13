/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 17:05:50 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:55:02 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <string.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	a;
	size_t	lendest;
	size_t	lensrc;

	a = 0;
	lendest = ft_strlen(dest);
	lensrc = ft_strlen(src);
	if (size > (lendest + 1))
	{
		while (a < (size - lendest - 1))
		{
			dest[lendest + a] = src[a];
			a++;
		}
		dest[lendest + a] = '\0';
	}
	if (size >= lendest)
		return (lendest + lensrc);
	return ((lendest + lensrc) - (lendest - size));
}
