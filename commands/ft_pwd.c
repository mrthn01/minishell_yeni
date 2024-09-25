/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:00:24 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/19 19:00:55 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pwd command
void	ft_pwd(char *str)
{
	char	*pwd;
	
	if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
	{
		pwd = getcwd(NULL, 0);
		if (pwd != NULL)
		{
			printf("%s\n", pwd);
			free(pwd);
		}
		else
			perror("pwd error");
	}
	else
		return ;
}
