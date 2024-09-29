/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:02:55 by melcuman          #+#    #+#             */
/*   Updated: 2024/09/29 18:10:48 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_number_of_envp_var(void)
{
	int	i;

	i = 0;
	while (g_minishell.envp[i])
		i++;
	return (i);
}

int	ft_is_exist(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (g_minishell.envp[i])
	{
		j = 0;
		while (g_minishell.envp[i][j] && str[j])
		{
			if (str[j] == '=' && g_minishell.envp[i][j] == '=')
				return (i);
			if (str[j] != g_minishell.envp[i][j])
				break ;
			j++;
		}
		i++;
	}
	return (-1);
}

int	ft_check_equal_sign(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=' || ft_isdigit(str[0]))
	{
		print_error(NULL, "error: not a valid identifier", 1);
		return (0);
	}
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0)
		{
			print_error(NULL, "error: not a valid identifier", 1);
			return (0);
		}
		i++;
	}
	if (str[i] != '=')
		return (1);
	else if (ft_updated_strchr(&str[i], '=') == 1)
		return (1);
	return (0);
}

int	ft_check_envp_var(char *str)
{
	if (ft_isdigit(*str))
	{
		print_error(NULL, "error: not a valid identifier", 1);
		return (0);
	}
	return (1);
}
