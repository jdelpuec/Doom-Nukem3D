/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:23:38 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 14:58:15 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		len_s1;
	size_t		len_s2;
	char		*boeuf;

	i = 0;
	if (!(s1 && s2))
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (!(boeuf = ft_memalloc(len_s1 + len_s2 + 1)))
		return (NULL);
	while (i < len_s1)
	{
		boeuf[i] = s1[i];
		i++;
	}
	while (i < len_s1 + len_s2)
	{
		boeuf[i] = s2[i - len_s1];
		i++;
	}
	boeuf[i] = '\0';
	return (boeuf);
}
