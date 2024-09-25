/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasari <sebasari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:54:51 by sebasari          #+#    #+#             */
/*   Updated: 2023/10/21 14:05:12 by sebasari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)(big));
	i = 0;
	while (i < len && big[i])
	{
		j = 0;
		while (big[i + j] && little[j]
			&& little[j] == big[i + j] && len > (i + j))
			j++;
		if ((little[j] == '\0'))
			return ((char *)(big + i));
		i++;
	}
	return (0);
}
