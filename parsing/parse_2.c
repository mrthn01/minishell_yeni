/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:38:01 by melcuman          #+#    #+#             */
/*   Updated: 2024/09/29 16:38:31 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*parse(int in_file, int out_file, t_minishell *mini)
{
	t_parse	*current;
	t_list	*token;
	t_parse	*initial;

	token = mini->nodes_t;
	current = init_cmd(in_file, out_file);
	initial = current;
	while (token != NULL)
	{
		if ((token->type >= 1 && token->type <= 4) && token->next)
			adjust_redirecs(&token, &current);
		else if (token->type == STRING)
			add_arguments(&token, &current);
		else if (token->type == PIPE && token->next)
			handle_pipes(&token, &current);
		else
			token = token->next;
	}
	mini->nodes_p = initial;
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
