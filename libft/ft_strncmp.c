/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 18:30:43 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 16:09:43 by ebonafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	while ((s1[a] || s2[b]) && (a < n))
	{
		if ((s1[a] - s2[b]) != 0)
			return ((unsigned char)s1[a] - (unsigned char)s2[b]);
		a++;
		b++;
	}
	return (0);
}
