/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 18:19:33 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/21 12:19:57 by ebonafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/libft.h"

static int	ft_line(const char *s, char c)
{
	int a;
	int b;

	a = 0;
	b = 0;
	while (s[a] == c)
		a++;
	while (s[a] != c && s[a] != '\0')
	{
		a++;
		if (s[a] == c)
			b++;
		while (s[a] == c)
			a++;
	}
	if (s[a - 1] != c)
		b++;
	if (s[0] == '\0')
		b--;
	return (b);
}

static int	ft_column(const char *s, char c)
{
	int	max;
	int b;
	int a;

	max = 0;
	b = 0;
	a = 0;
	while (s[a] == c)
		a++;
	while (s[a] != c && s[a] != '\0')
	{
		a++;
		b++;
		if (b > max)
			max = b;
		while (s[a] == c)
		{
			b = 0;
			a++;
		}
	}
	return (max + 1);
}

static char	*ft_insert(const char *s, char c, char *str, int mot)
{
	int a;
	int b;
	int d;

	d = 0;
	a = 0;
	b = -1;
	while (s[a] == c)
		a++;
	while (s[a] && s[a] != c)
	{
		a--;
		while (s[++a] != c && s[a] && d == mot)
			str[++b] = s[a];
		if (d != mot)
			a++;
		while (s[a] == c)
		{
			a++;
			if (s[a] != c)
				d++;
		}
	}
	str[++b] = '\0';
	return (str);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		a;
	int		lon;
	int		larg;

	a = -1;
	if (!s)
		return (NULL);
	larg = ft_line(s, c);
	lon = ft_column(s, c);
	str = (char **)malloc(sizeof(char *) * (larg + 1));
	if (!str)
		return (NULL);
	while (++a < larg)
	{
		str[a] = (char *)malloc(sizeof(char) * lon);
		if (!str[a])
			return (NULL);
		if (s[0] == '\0')
			str[a] = NULL;
		else
			str[a] = ft_insert(s, c, str[a], a);
	}
	str[a] = NULL;
	return (str);
}
