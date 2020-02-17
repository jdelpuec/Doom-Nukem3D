/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 10:12:38 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 15:00:13 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *str, int c)
{
	int len;
	int i;

	len = ft_strlen(str);
	i = 0;
	while (i <= len)
	{
		if (str[len - i] == (unsigned char)c)
			return ((char *)str + len - i);
		i++;
	}
	return (NULL);
}
