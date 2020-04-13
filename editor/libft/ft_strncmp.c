/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 18:30:43 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:55:27 by lubernar         ###   ########.fr       */
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
