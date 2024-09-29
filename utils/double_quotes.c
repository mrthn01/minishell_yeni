/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:05:31 by sebasari          #+#    #+#             */
/*   Updated: 2024/09/29 15:47:29 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_double_quotes_check(char *str, int index)
{
	if (ft_even_odd(str, '\"') % 2 == 1)
		return (1);
	if (str[ft_strlen(str) - 2] == '\\' && str[ft_strlen(str) - 3] != '\\')
		return (1);
	(void)index;
	return (0);
}

int	ft_double_quotes_finised(char *input, int index)
{
	while (input[index])
	{
		if (ft_double_quotes_check(input, index))
			return (1);
		index++;
	}
	return (0);
}

int	ft_even_odd(char *str, char c)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			counter++;
		i++;
	}
	return (counter);
}
