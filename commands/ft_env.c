/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:02:10 by melcuman          #+#    #+#             */
/*   Updated: 2024/09/29 18:02:11 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char	**input)
{
	char	**envp;

	envp = g_minishell.envp;
	if (input[1])
	{
		printf("error: No such file or directory.\n");
		return ;
	}
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
}
