/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasari <sebasari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:22:46 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/27 18:11:27 by sebasari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

void	ft_execute(char *full_path, char **str)
{
	printf("gecti \n");
	if (g_minishell.flag2 == 0)
	{
		execve(full_path, str, g_minishell.envp);
		// ft_clean_all() -> free
		// ft_clean_mess() -> free
		print_error(str[0], ": Permission denied\n", 126);
		exit(126);
	}
	else
	{
	//	ft_clean_all() -> free
	//	ft_clean_mess() -> free
		exit(1);
	}
}

char	*ft_str_join2(char *str)
{
	char	*str_new;
	int		i;
	int		len;
	int		j;

	len = 0;
	i = 1;
	while (str[i])
	{
		if (str[i] == '/')
			break ;
		i++;
	}
	j = i;
	while (str[i++])
		len++;
	i = j;
	j = 0;
	str_new= malloc(sizeof(char) * (len + 1));
	while (str[i])
		str_new[j++] = str[i++];
	return (str_new);
}

// search command path
char	*ft_search_path(char *str, char *path)
{
	char	*full_path;
	char	*command;
	char	*tok;

	if (*str != '/')
		command = ft_strjoin("/", str);
	else
		command = ft_str_join2(str);
	tok = ft_strtok(path, ":");
	while (tok != NULL)
	{
		full_path = ft_strjoin(tok, command);
		if (access(full_path, F_OK) == 0)
		{
			free(command);
			return (full_path);
		}
		else
		{
			free(full_path);
			tok = ft_strtok(NULL, ":");
		}
	}
	free(command);
	print_error(str, ": command not found\n", 127);
	return (NULL);
}

char	*ft_my_get_env(char **envp, char *str)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0)
			return (ft_envp_var(envp[i], ft_strlen(str)));
		i++;
	}
	return (NULL);
}

int	ft_check_if_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
		{
			return (i);
		}
		i++;
	}
	return (0);
}

// execve handler
void	ft_execute_execve(char **str)
{
	char	*full_path;
	char	*path;

	full_path = NULL;
	path = ft_my_get_env(g_minishell.envp, "PATH");
	if (path == NULL)
	{
		print_error(str[0], ": No such file or directory\n", 127);
		exit(g_minishell.exit_status);
	}
	if (ft_check_if_path(str[0]) == 0)
	{
		full_path = ft_search_path(str[0], path);
		if (full_path == NULL)
		{
			free(path);
			exit(g_minishell.exit_status);
		}
		else
			ft_execute(full_path, str);
		free(full_path);
	}
	else
		ft_execute(str[0], str);
	free(path);
}
