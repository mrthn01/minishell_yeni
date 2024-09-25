/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasari <sebasari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:46:25 by sebasari          #+#    #+#             */
/*   Updated: 2023/10/27 12:15:58 by sebasari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	unsigned char	*ptrchr;
	size_t			i;

	i = 0;
	ptr = malloc(nmemb * size);
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
