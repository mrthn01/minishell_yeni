/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_controll.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasari <sebasari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:07:19 by sebasari          #+#    #+#             */
/*   Updated: 2024/09/17 13:41:52 by sebasari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_check(t_list *tmp_token, t_list *tmp_prev)
{
	if (tmp_token->type == PIPE)
	{
		if (!tmp_prev || tmp_prev->type == PIPE)
			return (1);
		else if (!tmp_token->next)
			return (1);
	}
	return (0);
}

int	redic_check(t_list *tmp_token)
{
	if (tmp_token->type == SMALLER || tmp_token->type == GREATER || tmp_token->type == HERE_DOC || tmp_token->type == APPEND)
	{
		{
			if (!tmp_token->next || tmp_token->next->type != STRING)
				return (1);
		}
	}
	return (0);
}

int	fixed_check(t_list *tmp_token)
{
	if (tmp_token->type != STRING && tmp_token->type != GREATER
			&& tmp_token->type != APPEND && tmp_token->type != SMALLER
			&& tmp_token->type != HERE_DOC && tmp_token->type != PIPE)
			return (1);
	return (0);
}

int	ft_syntax_check(t_minishell *mini)
{
	t_list	*tmp;
	t_list	*tmp_previous;

	tmp = mini->nodes_t;
	tmp_previous = mini->nodes_t;
	while (tmp != NULL)
	{
		if (fixed_check(tmp) == 1)
		{
			print_error(NULL, "minishell: syntax error\n", 2);
			return (1);
		}
		else if (redic_check(tmp) == 1)
		{
			print_error(NULL, "minishell: syntax error\n", 2);
			return (1);
		}
		else if (pipe_check(tmp, tmp_previous) == 1)
		{
			print_error(NULL, "minishell: syntax error\n", 2);
			return (1);
		}
		tmp_previous = tmp;
		tmp = tmp->next;
	}
	return (0);
}