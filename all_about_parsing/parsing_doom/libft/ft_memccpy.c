/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 15:59:19 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 14:15:08 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memccpy(void *dest, void const *src, int c, size_t n)
{
	unsigned int	i;
	char			*dest1;
	char			*src1;
	char			c1;

	dest1 = (char *)dest;
	src1 = (char *)src;
	c1 = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		dest1[i] = src1[i];
		if (src1[i] == c1)
			return (&dest1[i] + 1);
		i++;
	}
	return (NULL);
}
