/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:00:52 by melcuman          #+#    #+#             */
/*   Updated: 2024/09/29 15:51:32 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

void	free_token(t_list *token)
{
	t_list	*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		token = token->next;
		ft_lstdelone(tmp, del);
		tmp = token;
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
		i = 0;
		parse = parse->next;
		while (tmp->args[i] != NULL)
		{
			free(tmp->args[i]);
			i++;
		}
		free(tmp->args);
		if (tmp->file != NULL)
			free_file(tmp->file);
		free(tmp);
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
