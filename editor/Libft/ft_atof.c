/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 14:23:07 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/16 14:24:07 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_end_atof(char *s, unsigned long i, float res)
{
	unsigned long	dec;

	dec = 1;
	while (ft_isdigit(s[i]))
	{
		res *= 10;
		res += (int)(s[i++] - '0');
	}
	if (s[i] == ',' || s[i] == '.')
	{
		i++;
		while (ft_isdigit(s[i]))
		{
			dec *= 10;
			res += (float)(s[i++] - '0') / (float)dec;
		}
	}
	return (res);
}

float	ft_atof(char *s)
{
	float           res;
	int             signe;
	unsigned long	i;

	res = 0.f;
	signe = 1;
	i = 0;
	if (s)
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (s[i] == '+' || s[i] == '-')
		{
			if (s[i++] == '-')
				signe = -1;
		}
		res = ft_end_atof(s, i, res);
	}
	if (signe == -1)
		res = -res;
	return (res);
}