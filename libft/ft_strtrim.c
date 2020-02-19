/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:55:04 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:56:08 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

static int	ft_countdeb(char const *s)
{
	int a;
	int nb;

	a = 0;
	nb = 0;
	while (s[a] == ' ' || s[a] == '\n' || s[a] == '\t' || s[a] == '\f'
				|| s[a] == '\r' || s[a] == '\v')
	{
		nb++;
		a++;
	}
	if (s[a] == '\0')
		return (-1);
	return (nb);
}

static int	ft_countfin(char const *s)
{
	int a;
	int nb;

	a = ft_strlen(s) - 1;
	nb = 0;
	while ((s[a] == ' ' || s[a] == '\n' || s[a] == '\t' || s[a] == '\f'
				|| s[a] == '\r' || s[a] == '\v') && a > 0)
	{
		a--;
		nb++;
	}
	return (nb);
}

char		*ft_strtrim(char const *s)
{
	size_t	a;
	size_t	b;
	int		nb;
	int		nb2;
	char	*s2;

	a = 0;
	nb = ft_countdeb(s);
	nb2 = ft_countfin(s);
	b = (ft_strlen(s) - (nb + nb2));
	if (nb == -1 && nb2 == 0)
		b = 1;
	s2 = (char*)malloc(sizeof(char) * b + 1);
	if (s2 == NULL)
		return (NULL);
	while (a < b && b > 1)
	{
		s2[a] = s[nb];
		a++;
		nb++;
	}
	s2[a] = '\0';
	return (s2);
}
