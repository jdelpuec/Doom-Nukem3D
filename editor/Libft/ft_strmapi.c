/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:48:27 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 14:59:02 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
		didi[i] = f(i, s[i]);
		i++;
	}
	return (didi);
}
