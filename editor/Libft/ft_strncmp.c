/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 14:28:08 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 14:32:42 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	unsigned int i;

	i = 0;
	while ((s1[i] == s2[i]) && (i < n))
	{
		if (s1[i] == '\0' || s2[i] == '\0')
			return (0);
		i++;
	}
	if (i == n)
		return (0);
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
