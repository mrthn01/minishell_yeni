/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasari <sebasari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:09:26 by sebasari          #+#    #+#             */
/*   Updated: 2023/10/21 15:44:08 by sebasari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1a;
	unsigned char	*s2a;

	s1a = (unsigned char *)s1;
	s2a = (unsigned char *)s2;
	i = 0;
	while (s1a[i] && s2a[i] && i < n)
	{
		if (s1[i] != s2[i])
		{
			return (s1a[i] - s2a[i]);
		}
		i++;
	}
	if (i < n)
	{
		return (s1a[i] - s2a[i]);
	}
	return (0);
}
