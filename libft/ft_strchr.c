/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 14:48:20 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/09 12:28:41 by ebonafi          ###   ########.fr       */
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
