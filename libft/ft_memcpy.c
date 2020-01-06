/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:35:53 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 16:00:34 by ebonafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memcpy(void *dest, void const *src, size_t n)
{
	size_t a;

	a = 0;
	while (a < n)
	{
		((char*)dest)[a] = ((char*)src)[a];
		a++;
	}
	return (dest);
}
