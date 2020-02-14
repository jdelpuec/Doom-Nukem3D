/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 16:17:03 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 15:01:14 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*didi;
	size_t	len_s;
	size_t	end;
	size_t	start;

	if (!(s))
		return (NULL);
	start = 0;
	len_s = ft_strlen(s);
	end = len_s - 1;
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		start++;
	while ((s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
			&& len_s != 0 && end != 0)
		end--;
	if (end == 0 || len_s == 0)
	{
		didi = (char *)malloc(sizeof(char) * 1);
		*didi = '\0';
		return (didi);
	}
	didi = ft_strsub(s, start, end - start + 1);
	return (didi);
}
