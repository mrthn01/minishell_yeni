/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:01:06 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/27 11:11:10 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get current pwd (old pwd)
void	ft_get_current_pwd(void)
{
	g_minishell.old_pwd = getcwd(NULL, 0);
}

// update pwd
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

// home
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

// cd command
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
			print_error(NULL, "erro: failed to change directory.\n", 1);
			return ;
		}
		g_minishell.exit_status = 0;
		ft_update_pwd();
	}
	else
		ft_go_home();
}
