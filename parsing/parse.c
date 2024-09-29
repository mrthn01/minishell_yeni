/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:46:22 by sebasari          #+#    #+#             */
/*   Updated: 2024/09/29 16:38:25 by melcuman         ###   ########.fr       */
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
	t_parse	*new_current;

	new_current = init_cmd((*old_current)->in_file, (*old_current)->out_file);
	(*old_current)->next = new_current;
	(*old_current) = (*old_current)->next;
	(*token) = (*token)->next;
}
