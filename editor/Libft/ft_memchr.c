/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:50:05 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 14:15:41 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(void const *str, int c, size_t n)
{
	unsigned char	a;
	unsigned int	i;

	i = 0;
	a = (unsigned char)c;
	while (i < n)
	{
		if (((unsigned char *)str)[i] == a)
			return ((unsigned char *)&str[i]);
		i++;
	}
	return (NULL);
}
