/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 15:24:32 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 16:00:25 by ebonafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_memcmp(void const *s1, void const *s2, size_t n)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;
	size_t			a;

	tmp1 = (unsigned char*)s1;
	tmp2 = (unsigned char*)s2;
	a = 0;
	if (s1 == s2)
		return (0);
	while (a < n)
	{
		if (tmp1[a] != tmp2[a])
			return (tmp1[a] - tmp2[a]);
		a++;
	}
	return (0);
}
