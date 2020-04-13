/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 13:19:02 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:54:16 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strcat(char *dest, char const *src)
{
	int a;
	int b;

	a = 0;
	b = 0;
	while (dest[a])
	{
		a++;
	}
	while (src[b])
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	dest[a] = '\0';
	return (dest);
}
