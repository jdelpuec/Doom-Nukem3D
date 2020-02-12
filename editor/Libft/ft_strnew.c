/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:14:22 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 14:59:51 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char			*boeuf;
	size_t			i;

	i = 0;
	if (!(boeuf = ft_memalloc(size + 1)))
		return (NULL);
	while (i < size)
	{
		boeuf[i] = '\0';
		i++;
	}
	boeuf[i] = '\0';
	return (boeuf);
}
