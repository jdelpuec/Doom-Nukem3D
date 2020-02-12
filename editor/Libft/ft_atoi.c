/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 14:03:50 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 14:03:37 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int			i;
	int			neg;
	long long	result;

	i = 0;
	result = 0;
	neg = 0;
	while (str[i] >= 7 && str[i] <= 13 ^ str[i] == ' ')
		i++;
	if (str[i] == '-')
		neg = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10;
		result = result + (str[i] - 48);
		i++;
		if (result < 0)
			return (neg ? 0 : -1);
	}
	return (neg ? (int)-result : (int)result);
}
