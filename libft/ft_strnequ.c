/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 14:02:51 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 16:10:14 by ebonafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t a;

	a = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (s1[a] && s2[a] && a < n)
	{
		if (s1[a] != s2[a])
			return (0);
		a++;
	}
	if (s1[a] != s2[a] && a < n)
		return (0);
	return (1);
}
