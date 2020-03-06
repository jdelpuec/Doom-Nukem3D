/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 14:48:20 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:54:21 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strchr(char const *s, int c)
{
	int a;

	a = 0;
	while (s[a] && s[a] != (char)c)
	{
		a++;
	}
	if (s[a] == (char)c)
		return ((char*)&s[a]);
	return (NULL);
}
