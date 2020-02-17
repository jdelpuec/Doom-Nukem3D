/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:40:00 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 14:58:50 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*didi;
	unsigned int	i;

	if (!(s) || !(f))
		return (NULL);
	i = ft_strlen(s);
	if (!(didi = ft_memalloc(i + 1)))
		return (NULL);
	i = 0;
	while (s[i])
	{
		didi[i] = f(s[i]);
		i++;
	}
	return (didi);
}
