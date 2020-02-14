/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 14:34:58 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 14:33:07 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dest, char const *src, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	while (src[j] != '\0')
		j++;
	i = 0;
	while ((i < n) && (i <= j))
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
