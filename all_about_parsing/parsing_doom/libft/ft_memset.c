/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 16:38:40 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 14:18:06 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *str, int c, size_t len)
{
	int		i;
	char	*str1;

	str1 = (char *)str;
	i = 0;
	while (len)
	{
		str1[i] = c;
		i++;
		len--;
	}
	return (str1);
}
