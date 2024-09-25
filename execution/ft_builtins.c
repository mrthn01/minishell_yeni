/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:19:50 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/23 14:30:50 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_or_not(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, "cd", ft_strlen("cd")) == 0)
		return (1);
	if (ft_strncmp(str, "pwd", ft_strlen("pwd")) == 0)
		return (2);
	if (ft_strncmp(str, "echo", ft_strlen("echo")) == 0)
		return (3);
	if (ft_strncmp(str, "env", ft_strlen("env")) == 0)
		return (4);
	if (ft_strncmp(str, "export", ft_strlen("export")) == 0)
		return (5);
	if (ft_strncmp(str, "unset", ft_strlen("unset")) == 0)
		return (6);
	return (0);
}

void	ft_execute_builtins(char **commands)
{
	int	type;

	type = ft_builtin_or_not(commands[0]);
	if (type == 1)
		ft_cd(commands);
	else if (type == 2)
		ft_pwd(*commands);
	else if (type == 3)
		ft_echo(commands);
	else if (type == 4)
		ft_env(commands);
	else if (type == 5)
		ft_export(commands);
	else if (type == 6)
		ft_unset(commands);
}
