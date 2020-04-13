/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:27:56 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:54:47 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	unsigned int a;

	a = 0;
	if (s == NULL || f == NULL)
		return ;
	while (s[a])
	{
		f((char*)&s[a]);
		a++;
	}
}
