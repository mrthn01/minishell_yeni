/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:46:22 by sebasari          #+#    #+#             */
/*   Updated: 2024/09/25 00:25:00 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse	*init_cmd(int in_file, int out_file)
{
	t_parse	*current;

	current = malloc(sizeof(t_parse));
	current->in_file = in_file;
	current->out_file = out_file;
	current->file = NULL;
	current->next = NULL;
	current->args = ft_calloc(2, sizeof(char *));
	return (current);
}

void	add_new_node(t_parse *current, t_parse **list)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	list[i] = current;
	list[i + 1] = NULL;
}

void	add_arguments(t_list **token, t_parse **current)
{
	int		i;
	char	**arg;
	
	i = 0;
	while ((*current)->args[i])
		i++;
	arg = ft_calloc((i + 2), sizeof(char *));
	arg[i + 1] = NULL;
	arg[i] = ft_strdup((char *)(*token)->content);
	while (i--)
		arg[i] = ft_strdup((*current)->args[i]);
	ft_split_free((*current)->args);
	(*current)->args = arg;
	(*token) = (*token)->next;
}

void	adjust_redirecs(t_list **token, t_parse **current)
{
	t_file	*file;
	t_file	*tmp_list;

	tmp_list = (*current)->file;
	file = malloc(sizeof(t_file));
	file->next = NULL;
	file->type = (*token)->type;
	(*token) = (*token)->next;
	file->after = ft_strdup((char *)(*token)->content);
	if (!tmp_list)
		(*current)->file = file;
	else
	{
		while (tmp_list->next)
			tmp_list = tmp_list->next;
		tmp_list->next = file;
	}
	(*token) = (*token)->next;
}

void	handle_pipes(t_list **token, t_parse **old_current)
{
	t_parse *new_current;

	new_current = init_cmd((*old_current)->in_file, (*old_current)->out_file);
	(*old_current)->next = new_current;
	(*token) = (*token)->next;
}

t_minishell	*parse(int in_file, int out_file, t_minishell *mini)
{
	t_parse	*current;
	t_list	*token;

	token = mini->nodes_t;
	while (token != NULL)
	{
		current = init_cmd(in_file, out_file);
		while (token != NULL)
		{
			if ((token->type >= 1 && token->type<= 4) && token->next)
				adjust_redirecs(&token, &current);
			else if(token->type == STRING)
				add_arguments(&token, &current);
			else if (token->type == PIPE && token->next)
				handle_pipes(&token, &current);
			else
				token = token->next;
		}
	}
	mini->nodes_p = current;
	mini = create_out_dup_list(mini);
	return (mini);
}

t_minishell	*create_out_dup_list(t_minishell *mini)
{
	t_fd		*fd;
	t_parse		*temp;
	t_file		*file;

	fd = (t_fd *)malloc(sizeof(t_fd));
	g_minishell.fd = fd;
	temp = mini->nodes_p;
	while (temp != NULL)
	{
		file = temp->file;
		while (file)
		{
			fd->out = dup(STDOUT_FILENO);
			fd->in = dup(STDIN_FILENO);
			if (file->next || temp->next != NULL)
				fd->next = (t_fd *)malloc(sizeof(t_fd));
			else
				fd->next = NULL;
			fd = fd->next;
			file = file->next;
		}
		temp = temp->next;
	}
	return (mini);
}
