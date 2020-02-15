/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 11:23:14 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 15:00:24 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strrev(char *str)
{
	size_t	i;
	size_t	end;
	char	*res;

	i = 0;
	end = ft_strlen(str);
	if (!(res = (char *)malloc(sizeof(char) * end)))
		return (NULL);
	while (str[i])
	{
		res[i] = str[end - 1];
		i++;
		end--;
	}
	res[i] = '\0';
	return (res);
}
