/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:50:32 by melcuman          #+#    #+#             */
/*   Updated: 2024/09/29 18:06:10 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_open_pipes(int **fd_pipe)
{
	int	i;

	i = 0;
	while (fd_pipe[i])
	{
		free(fd_pipe[i]);
		i++;
	}
	free(fd_pipe);
}

void	ft_free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	clean_the_mess(void)
{
	int	i;

	i = 0;
	if (g_minishell.paths)
	{
		while (g_minishell.paths[i])
		{
			free(g_minishell.paths[i]);
			i++;
		}
		free(g_minishell.paths);
	}
	g_minishell.paths = NULL;
	i = 0;
	if (g_minishell.envp)
	{
		while (g_minishell.envp[i])
		{
			free(g_minishell.envp[i]);
			i++;
		}
		free(g_minishell.envp);
	}
	g_minishell.envp = NULL;
}

void	free_all(char *str)
{
	if (g_minishell.str)
		free(str);
	if (g_minishell.input)
		free_input();
	if (g_minishell.nodes_t)
		free_token(g_minishell.nodes_t);
	if (g_minishell.nodes_p)
	{
		free_parse(g_minishell.nodes_p);
	}
	if (g_minishell.fd)
		free_fd(g_minishell.fd);
	g_minishell.token_num2 = 0;
}
