/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:06:40 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/23 14:29:30 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

// store environment variable and later access through global variable
char	**ft_store_envp(char **envp)
{
	char	**store_env;
	int		i;

	i = 0;
	while(envp[i])
		i++;
	store_env = malloc(sizeof(char *) * (i + 1));
	if (!store_env)
		return (0);
	i = 0;
	while (envp[i])
		{
			store_env[i] = ft_strdup(envp[i]);
			i++;
		}
	store_env[i] = 0;
	return (store_env);
}

// init minishell states
void	ft_init(char **envp)
{
	g_minishell.envp = ft_store_envp(envp);
	g_minishell.exit_status = 0;
	g_minishell.nodes_p = NULL; // parsing
	g_minishell.fd = NULL;
	g_minishell.error = 0;
}
