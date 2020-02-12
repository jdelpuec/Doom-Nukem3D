/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:15:28 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 14:17:34 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dest, void const *src, size_t n)
{
	unsigned int i;

	i = 0;
	while (n--)
	{
		if (src < dest)
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
		else
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
