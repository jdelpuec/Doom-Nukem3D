/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:40:17 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 14:56:49 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char const *str, int c)
{
	int i;
	int len;

	len = ft_strlen(str);
	i = 0;
	while (i <= len)
	{
		if (str[i] == c)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
