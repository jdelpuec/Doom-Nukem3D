/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:15:40 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 14:10:03 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static char	*int_mini(char *s)
{
	s[0] = '-';
	s[1] = '2';
	s[2] = '1';
	s[3] = '4';
	s[4] = '7';
	s[5] = '4';
	s[6] = '8';
	s[7] = '3';
	s[8] = '6';
	s[9] = '4';
	s[10] = '8';
	return (s);
}

static void	taille_de_n(long n, int *i)
{
	if (n == -2147483648)
		*i = 12;
	else
	{
		if (n < 0)
		{
			n = -n;
			(*i)++;
		}
		if (n >= 10)
			taille_de_n(n / 10, i);
		*i = *i + 1;
	}
}

static void	decoupage_n(char *str, int nb, int i, int n)
{
	int j;

	j = 0;
	if (nb == -2147483648)
		str = int_mini(str);
	else
	{
		if (nb < 0)
		{
			str[0] = '-';
			nb = -nb;
		}
		if (nb >= 10)
			decoupage_n(str, nb / 10, i + 1, n);
		str[n - i] = nb % 10 + '0';
	}
}

char		*ft_itoa(int n)
{
	char	*didi;
	int		len_n;
	long	long_n;

	long_n = n;
	len_n = 0;
	taille_de_n(long_n, &len_n);
	if (!(didi = (char *)malloc(sizeof(char) * (len_n + 1))))
		return (NULL);
	decoupage_n(didi, long_n, 1, len_n);
	didi[len_n] = '\0';
	return (didi);
}
