/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasari <sebasari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:46:25 by sebasari          #+#    #+#             */
/*   Updated: 2024/09/29 13:48:54 by sebasari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	unsigned char	*ptrchr;
	size_t			i;

	i = 0;
	ptrchr = NULL;
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ptrchr = ptr;
	if (ptr == NULL)
		return (ptr);
	while (size * nmemb > i)
	{
		ptrchr[i] = 0;
		i++;
	}
	return (ptr);
}
