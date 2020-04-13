/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 15:20:30 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:52:57 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memchr(void const *s, int c, size_t n)
{
	size_t	a;

	a = 0;
	while (a < n)
	{
		if (((unsigned char*)s)[a] == (unsigned char)c)
			return ((void*)(s + a));
		else
			a++;
	}
	return (0);
}
