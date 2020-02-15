/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 14:37:02 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 14:39:01 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char const *str, char const *to_find)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] != '\0')
	{
		while (str[j + i] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return ((char *)str + i);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
