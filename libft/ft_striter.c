/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:27:56 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 16:06:22 by ebonafi          ###   ########.fr       */
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
