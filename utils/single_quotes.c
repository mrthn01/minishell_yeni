/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasari <sebasari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:05:34 by sebasari          #+#    #+#             */
/*   Updated: 2024/09/24 21:18:13 by sebasari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_single_quotes_finised(char *input, int index)
{
	while (input[index])
	{
		if (ft_even_odd(input, '\'') % 2 == 1)
			return (1);
		index++;
	}
	return (0);
}

int	ft_quotes_num(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			return (i);
		i++;
	}
	return (0);
}

int ft_is_quotes_there(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\"')
			return (2);
		if (input[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	ft_quotes(char *input)
{
	int index;

	index = 0;
	if (ft_is_quotes_there(input) == 1)
	{
		index = ft_quotes_num(input);
		if (ft_single_quotes_finised(input, index) == 1)
			return (1);
	}
	else if (ft_is_quotes_there(input) == 2)
	{
		index = ft_quotes_num(input);
		if (ft_double_quotes_finised(input, index) == 1)
			return (1);
	}
	return (0);
}

int	ft_last_index_check(char *str)
{
	if (str[ft_strlen(str) - 1] == '\\')
		return (1);
	return (0);
}