/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 14:41:49 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 14:34:41 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(char const *str, char const *to_find, size_t n)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	while (i < n && str[i])
	{
		j = 0;
		while (i + j < n && str[i + j] == to_find[j] && to_find[j])
			j++;
		if (!(to_find[j]))
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
