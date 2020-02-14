/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 10:32:14 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 14:29:35 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcat(char *dest, char const *src, size_t len)
{
	unsigned int i;
	unsigned int j;
	unsigned int k;

	i = 0;
	j = 0;
	k = 0;
	while (dest[k] != '\0')
		k++;
	while (src[j] != '\0')
		j++;
	while ((i < j) && (k + i < len - 1) && len != 0)
	{
		dest[i + k] = src[i];
		i++;
	}
	dest[k + i] = '\0';
	if (len < k)
		return (j + len);
	return (j + k);
}
