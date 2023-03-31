/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:02:34 by hucorrei          #+#    #+#             */
/*   Updated: 2022/10/24 10:50:14 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlst;
	t_list	*tmp;

	nlst = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		tmp = malloc(sizeof(t_list));
		if (!tmp)
		{
			ft_lstclear(&nlst, del);
			return (NULL);
		}
		tmp->content = (*f)(lst->content);
		tmp->next = NULL;
		ft_lstadd_back(&nlst, tmp);
		lst = lst->next;
	}
	return (nlst);
}
