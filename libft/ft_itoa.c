/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasari <sebasari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:30:15 by sebasari          #+#    #+#             */
/*   Updated: 2023/10/21 15:26:06 by sebasari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_total(int n)
{
	size_t	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n == 0)
		return (1);
	else if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_string(int total, int n, char *str)
{
	while (total > 0)
	{
		if (n == -2147483648)
		{
			str[0] = '-';
			str[total - 1] = '8';
			n = n / 10;
			n = n * -1;
			total--;
		}
		else if (n < 0)
		{
			n = n * -1;
			str[0] = '-';
		}
		if (n > 0)
		{
			str[total - 1] = '0' + n % 10;
			n = n / 10;
		}
		total--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	total;

	total = ft_total(n);
	str = malloc(total + 1);
	if (!str)
		return (0);
	str[total] = '\0';
	if (n == 0)
		str[0] = '0';
	str = ft_string(total, n, str);
	return (str);
}
