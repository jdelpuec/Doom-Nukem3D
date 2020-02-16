/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+ */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 19:06:29 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 15:58:00 by ebonafi          ###   ########.fr       */
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
