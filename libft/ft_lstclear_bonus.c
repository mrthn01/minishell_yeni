/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasari <sebasari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:27:36 by sebasari          #+#    #+#             */
/*   Updated: 2024/02/18 17:31:17 by sebasari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*tmp1;

	if (!lst || !del || !*lst)
		return ;
	tmp = *lst;
	tmp1 = *lst;
	while (tmp)
	{
		tmp1 = tmp1 -> next;
		ft_lstdelone(tmp, del);
		tmp = tmp1;
	}
}
