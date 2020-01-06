/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 18:56:59 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/11 12:38:27 by ebonafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

char		*ft_strjoin2(char *s1, char *s2, int b)
{
	char	*s3;
	int		a;
	int		c;

	a = 0;
	c = 0;
	if (s1)
		a = 1;
	if (s2)
		c = 1;
	s1 = (s1 == NULL) ? "" : s1;
	s2 = (s2 == NULL) ? "" : s2;
	s3 = ft_strjoin(s1, s2);
	if (a == 1 && (b == 1 || b == 2))
		free(s1);
	if (c == 1 && (b == 2 || b == 3))
		free(s2);
	return (s3);
}
