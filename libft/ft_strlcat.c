/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 17:05:50 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 16:07:33 by ebonafi          ###   ########.fr       */
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
