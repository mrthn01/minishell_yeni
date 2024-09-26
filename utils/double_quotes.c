/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasari <sebasari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:05:31 by sebasari          #+#    #+#             */
/*   Updated: 2024/09/26 14:42:59 by sebasari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dollar_len(char *str)
{
	int	dolar_sign;
	int	dolar_sign_len;

	dolar_sign = 0;
	dolar_sign_len = 0;
	while (str[dolar_sign])
	{
		if (str[dolar_sign] == '$')
		{
			dolar_sign++;
			while (str[dolar_sign++] != ' ')
				dolar_sign_len++;
		}
		dolar_sign++;
	}
	return (dolar_sign_len);
}

char	*ft_dollar_sign(char *str)
{
	char	*new_str;
	int		dolar_sign_len;
	int		i;
	int		j;

	j = 0;
	i = 0;
	dolar_sign_len = ft_dollar_len(str);
	if (dolar_sign_len == 0)
		return (str);
	new_str = malloc(sizeof(char) * (ft_strlen(str) - dolar_sign_len));
	while (str[i])
	{
		if (str[i] == '$')
			while (str[i] != ' ')
				i++;
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
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
		if (str[index] == '$')
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