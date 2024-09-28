/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:00:52 by melcuman          #+#    #+#             */
/*   Updated: 2024/09/28 17:15:35 by murathanelc      ###   ########.fr       */
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
	g_minishell.nodes_p = NULL;
}



void	free_fd(t_fd *fd)
{
	t_parse	*temp;
	t_file	*file;
	t_fd	*temp2;
	
	g_minishell.fd = fd;
	temp = g_minishell.nodes_p;
	while (temp != NULL)
	{
		file = temp->file;
		while (file)
		{
			temp2 = fd->next;
			free(fd);
			fd = temp2;
			file = file->next;
		}
		temp = temp->next;
	}
	free(fd);
	g_minishell.fd = NULL;
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

static void	free_input(void)
{
	int	i;

	i = 0;
	while (g_minishell.input[i])
	{
		free(g_minishell.input[i]);
		i++;
	}
	free(g_minishell.input);
	g_minishell.input = NULL;
}

void	free_all(char *str)
{
	if (str)
		free(str);
	if (g_minishell.input)
		free_input();
	if (g_minishell.nodes_t)
		free_token(g_minishell.nodes_t);
	if (g_minishell.nodes_p)
		free_parse(g_minishell.nodes_p);
	if (g_minishell.fd)
		free_fd(g_minishell.fd);
	g_minishell.token_num2 = 0;
}
