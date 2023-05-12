/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:22:04 by lwathar           #+#    #+#             */
/*   Updated: 2022/10/03 16:34:50 by lowathar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (lst == 0 || del == 0)
		return ;
	tmp = *lst;
	while (tmp != NULL)
	{
		*lst = tmp;
		ft_lstdelone(*lst, del);
		tmp = tmp->next;
	}
	*lst = NULL;
}
