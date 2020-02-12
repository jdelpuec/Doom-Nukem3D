/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 14:36:03 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 14:26:39 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strdup(char const *src)
{
	int i;
	int j;
	char*cpy;

	i = 0;
	j = 0;
	while (src[i] != '\0')
		i++;
	if (!(cpy = (char*)malloc(sizeof(*cpy) * (i + 1))))
		return (NULL);
	while (j <= i)
	{
		cpy[j] = src[j];
		j++;
	}
	cpy[j] = '\0';
	return (cpy);
}
