/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:35:53 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:53:05 by lubernar         ###   ########.fr       */
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
