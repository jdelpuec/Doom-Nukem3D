/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 14:51:57 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/09 12:30:41 by ebonafi          ###   ########.fr       */
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
