/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitlst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 12:45:16 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 16:11:54 by ebonafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_strsplitlst(char const *s, char c)
{
	int		a;
	char	**tab;
	t_list	**alst;
	t_list	*lst;
	t_list	*new;

	a = 1;
	alst = NULL;
	lst = NULL;
	tab = ft_strsplit(s, c);
	if (tab == NULL)
		return (NULL);
	lst = ft_lstnew(tab[0], ft_strlen(tab[0]));
	*alst = lst;
	new = lst;
	while (tab[a] != NULL)
	{
		new->content = tab[a];
		new->content_size = ft_strlen(tab[a]);
		ft_lstaddend(alst, new);
		a++;
	}
	return (lst);
}
