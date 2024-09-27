/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:00:52 by melcuman          #+#    #+#             */
/*   Updated: 2024/09/27 19:44:14 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

void	free_token(t_list *token)
{
	t_list *tmp;

	tmp = token;
	while (tmp != NULL)
	{
		ft_lstdelone(tmp, del);
		token = token->next;
		tmp = token;
		printf("gecti token \n");
	}
	free(tmp);
}

void	free_file(t_file *file)
{
	free(file->after);
	free(file);
}

void	free_parse(t_parse *parse)
{
	t_parse	*tmp;
	int		i;

	i = 0;
	tmp = parse;
	while (tmp != NULL)
	{
		while (tmp->args[i] != NULL)
			free(tmp->args[i++]);
		free(tmp->args);
		if (tmp->file != NULL)
			free_file(tmp->file);
		free(tmp);
		parse = parse->next;
		tmp = parse;
	}
	free(tmp);
}

void	free_fd(t_fd *fd)
{
	t_fd *tmp;

	tmp = fd;
	while (tmp != NULL)
	{
		// free(tmp);
		fd = fd->next;
		tmp = fd;
		printf("gecti fd\n");
	}
}

// clean all the stuff
void	clean_the_mess(void)
{
	int	i;

	i = 0;
	if (g_minishell.paths)
	{
		while (g_minishell.paths[i])
		{
			free(g_minishell.paths);
			i++;
		}
		free(g_minishell.paths);
	}
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
	if (str)
	{
		free(str);
	}
	if (g_minishell.nodes_t)
	{
		free_token(g_minishell.nodes_t);
	}
	if (g_minishell.nodes_p)
	{
		free_parse(g_minishell.nodes_p);
	}
}