/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasari <sebasari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:05:31 by sebasari          #+#    #+#             */
/*   Updated: 2024/09/24 21:18:26 by sebasari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_back_slash(char *str)
{
	printf("%s\n", str);
}

void	ft_dollar_sign(char *str)
{
	printf("%s\n", str);
}

int	ft_double_quotes_check(char *str, int index)
{
	if (ft_even_odd(str, '\"') % 2 == 1)
		return (1);
	if (str[ft_strlen(str) - 2] == '\\' && str[ft_strlen(str) - 3] != '\\')
		return (1);
	index++;
	while (str[index])
	{
		if (str[index] == '\\')
			ft_back_slash(str);
		else if (str[index] == '$')
			ft_dollar_sign(str);
		index++;
	}
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