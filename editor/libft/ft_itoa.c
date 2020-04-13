/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 11:50:58 by lubernar          #+#    #+#             */
/*   Updated: 2020/03/06 11:51:04 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

char		*ft_itoa(int n)
{
	int		b;
	char	*s;

	b = ft_numlen(n);
	s = (char*)malloc(sizeof(char) * b + 1);
	if (s == NULL)
		return (NULL);
	s[b] = '\0';
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		s[0] = '-';
		n = -n;
	}
	while (n >= 1 && s[b] != '-')
	{
		b--;
		s[b] = (n % 10) + 48;
		n = (n / 10);
	}
	return (s);
}
