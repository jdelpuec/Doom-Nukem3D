/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 13:31:17 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 16:09:26 by ebonafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strncat(char *dest, char const *src, size_t n)
{
	int a;
	int b;

	a = 0;
	b = 0;
	while (dest[a])
	{
		a++;
	}
	while (src[b] && n)
	{
		dest[a] = src[b];
		a++;
		b++;
		n--;
	}
	dest[a] = '\0';
	return (dest);
}
