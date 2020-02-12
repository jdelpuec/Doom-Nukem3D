/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 11:19:46 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 14:22:32 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	*ft_strlowcase(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] >= 'A') && (str[i] <= 'Z'))
		{
			str[i] = str[i] + 32;
		}
		i++;
	}
	return (str);
}

char		*ft_strcapitalize(char *str)
{
	int i;
	int j;

	ft_strlowcase(str);
	i = 0;
	j = 1;
	while (str[i] != '\0')
	{
		if ((str[i] >= 'a') && (str[i] <= 'z') && j)
		{
			str[i] = str[i] - 32;
		}
		i++;
		if (((str[i - 1] >= 'a') && (str[i - 1] <= 'z')) ||
				((str[i - 1] >= 'A') && (str[i - 1] <= 'Z')) ||
				((str[i - 1] >= '0') && (str[i - 1] <= '9')))
			j = 0;
		else
			j = 1;
	}
	return (str);
}
