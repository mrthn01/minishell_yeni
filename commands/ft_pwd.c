/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:00:24 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/27 01:31:07 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pwd command
void	ft_pwd(void)
{
	char	*pwd;
	
	pwd = getcwd(0, 0);
	if (!pwd)
		print_error(NULL, "error: no such file or directory.\n", 127);
	else
	{
		g_minishell.exit_status = 0;
		printf("%s\n", pwd);
	}
	free(pwd);
}
