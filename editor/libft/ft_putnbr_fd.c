/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 22:08:53 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:53:54 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putnbr_fd(long int n, int fd)
{
	if (n < 0)
	{
		n = -n;
		ft_putchar_fd('-', fd);
	}
	if (n < 10)
		ft_putchar_fd((n + 48), fd);
	else
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putnbr_fd((n % 10), fd);
	}
}
