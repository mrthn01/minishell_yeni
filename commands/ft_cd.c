/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:01:34 by melcuman          #+#    #+#             */
/*   Updated: 2024/09/29 18:01:48 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_current_pwd(void)
{
	g_minishell.old_pwd = getcwd(NULL, 0);
}

void	ft_update_pwd(void)
{
	char	*pwd;
	char	*temp;
	int		i;

	pwd = getcwd(NULL, 0);
	if (ft_is_exist("PWD=") != -1)
	{
		i = ft_is_exist("PWD");
		free(g_minishell.envp[i]);
		temp = ft_strjoin("PWD=", pwd);
		g_minishell.envp[i] = ft_strdup(temp);
		free(temp);
	}
	if (ft_is_exist("OLDPWD=") != -1)
	{
		i = ft_is_exist("OLDPWD=");
		free(g_minishell.envp[i]);
		temp = ft_strjoin("OLDPWD=", g_minishell.old_pwd);
		g_minishell.envp[i] = ft_strdup(temp);
		free(temp);
	}
	free(g_minishell.old_pwd);
	free(pwd);
}

void	ft_go_home(void)
{
	char	*temp;

	temp = ft_custom_getenv("HOME");
	ft_get_current_pwd();
	if (chdir(temp) == 0)
		g_minishell.exit_status = 0;
	else
		print_error(NULL, "error: Home directory not found.\n", 1);
	free(temp);
	ft_update_pwd();
}

void	ft_cd(char **str)
{
	if (str[1])
	{
		ft_get_current_pwd();
		if (str[2])
		{
			print_error(NULL, "error: too many arguments.\n", 1);
			return ;
		}
		else if (chdir(str[1]))
		{
			print_error(NULL, "error: failed to change directory.\n", 1);
			return ;
		}
		g_minishell.exit_status = 0;
		ft_update_pwd();
	}
	else
		ft_go_home();
}
