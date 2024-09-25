/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasari <sebasari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:34:26 by sebasari          #+#    #+#             */
/*   Updated: 2023/10/27 15:03:26 by sebasari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *memcpy, const void *src, size_t n)
{
	unsigned char	*str;
	unsigned char	*str1;
	size_t			i;

	i = 0;
	str = (unsigned char *)memcpy;
	str1 = (unsigned char *)src;
	if (!memcpy && !src)
		return (0);
	while ((i < n))
	{
		str[i] = str1[i];
		i++;
	}
	return (memcpy);
}
