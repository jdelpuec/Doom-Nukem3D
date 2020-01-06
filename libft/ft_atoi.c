/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 17:36:51 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 15:55:38 by ebonafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

static int	ft_a(char const *s, int a)
{
	int	neg;

	neg = 0;
	while (s[a] == '\t' || s[a] == '\f' || s[a] == '\n' || s[a] == '\r' ||
			s[a] == ' ' || s[a] == '+' || s[a] == '-' || s[a] == '\v')
	{
		a++;
	}
	return (a);
}

static int	ft_sign(char const *s, int a)
{
	int	neg;

	neg = 0;
	while (s[a] == '\t' || s[a] == '\f' || s[a] == '\n' || s[a] == '\r' ||
			s[a] == ' ' || s[a] == '+' || s[a] == '-' || s[a] == '\v')
	{
		if (s[a] == '-' && neg == 0)
			neg = 1;
		if ((s[a + 1] > '9' || s[a + 1] < '0') && neg == 1)
			return (3);
		if (s[a] == '+' && neg == 0)
			neg = 2;
		if ((s[a + 1] < '0' || s[a + 1] > '9') && neg == 2)
			return (3);
		a++;
	}
	return (neg);
}

int			ft_atoi(char const *s)
{
	int	a;
	int	nb;
	int	neg;

	nb = 0;
	a = ft_a(s, 0);
	neg = ft_sign(s, 0);
	if (neg == 3)
		return (0);
	while (s[a] <= '9' && s[a] >= '0')
	{
		nb = nb * 10 + s[a] - 48;
		a++;
	}
	if (neg == 1)
		return (-nb);
	if (neg == 2 || neg == 0)
		return (nb);
	return (0);
}
