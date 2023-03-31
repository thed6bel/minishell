/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:01:03 by hucorrei          #+#    #+#             */
/*   Updated: 2022/10/19 12:31:24 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*nextlst;

	if (!del)
		return ;
	tmp = *lst;
	while (tmp)
	{
		nextlst = tmp->next;
		ft_lstdelone(tmp, del);
		tmp = nextlst;
	}
	*lst = 0;
}
