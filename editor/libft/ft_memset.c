/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 14:51:57 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:53:19 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	size_t a;

	a = 0;
	while (a < len)
	{
		((char*)s)[a] = (unsigned char)c;
		a++;
	}
	return (s);
}
