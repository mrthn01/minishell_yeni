/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:08:59 by melcuman          #+#    #+#             */
/*   Updated: 2024/09/29 18:09:12 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
