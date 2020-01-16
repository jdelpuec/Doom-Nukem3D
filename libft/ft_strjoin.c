/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:28:07 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 16:06:51 by ebonafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		a;
	int		b;
	int		c;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	a = (ft_strlen(s1) + ft_strlen(s2) + 1);
	b = 0;
	c = 0;
	s3 = (char*)malloc(sizeof(char) * a);
	if (s3 == NULL)
		return (NULL);
	s3 = ft_strcpy(s3, s1);
	s3 = ft_strcat(s3, s2);
	return (s3);
}