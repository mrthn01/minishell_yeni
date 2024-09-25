/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasari <sebasari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:25:43 by sebasari          #+#    #+#             */
/*   Updated: 2024/09/24 21:00:08 by sebasari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_char_array(char **array)
{
	int i = 0;
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}

int	ft_controll_qoutes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	ft_special_type_index(char c)
{
	if (c == '<' || c == '>' || c == '|')
			return (1);
	return (0);
}

int	check_for_q(t_minishell *mini)
{
	char	*str;
	t_list	*token;

	token = mini->nodes_t;
	while (token != NULL)
	{
		str = (char *)token->content;
		if (ft_quotes(str) == 1)
			return (1);
		token = token->next;
	}
	return (0);
}

int	ft_updated_strchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_modify_string(char **old, char **new)
{
	free(*old);
	*old = ft_strdup(*new);
	free(*new);
}
