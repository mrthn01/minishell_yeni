/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:07:59 by sebasari          #+#    #+#             */
/*   Updated: 2024/09/29 16:49:54 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_special_type(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>' || input[i] == '|')
		{
			if ((input[i] == '>' && input[i + 1] == '>')
				|| (input[i] == '<' && input[i + 1] == '<' ))
				return (1);
			else
				return (1);
		}
		i++;
	}
	return (0);
}

t_minishell	*divide_accordingly(char *input, t_minishell *mini, int *index_num)
{
	int		i;
	int		len;
	int		start;

	start = 0;
	len = 0;
	i = 0;
	while (input[i])
	{
		if (!ft_special_type_index(input[i]))
		{
			while (input[i] && !ft_special_type_index(input[i]))
			{
				if (ft_is_quotes_there_index(input[i]))
				{
					i = ft_find_next_q(index, input);
					i++;
					break ;
				}
				else
					i++;
			}
			len = i - len;
			mini = ft_add_new_node(input, start, len, mini, index_num);
			start = i;
			len = 0;
		}
		else
		{
			if (input[i] && ft_special_type_index(input[i]))
			{
				if (input[i + 1] && ((input[i] == '<' && input[i + 1] == '<')
						|| (input[i] == '>' && input[i + 1] == '>')))
					len = 2;
				else
					len = 1;
				i += len;
				ft_find_the_type(input, start, len, mini, index_num);
				start = i;
				len = 0;
			}
		}
	}
	return (mini);
}

t_minishell	*ft_find_the_type(char *input, int start, int len,
	t_minishell *mini, int *index_num)
{
	if (input[start] == '|' && len == 1)
		mini = ft_get_pipe(input, start, len, mini, index_num);
	else if (input[start] == '<' && len == 2)
		mini = ft_get_redi_herodoc(input, start, len, mini, index_num);
	else if (input[start] == '>' && len == 2)
		mini = ft_get_redi_append(input, start, len, mini, index_num);
	else if (input[start] == '<' && len == 1)
		mini = ft_get_redi_in(input, start, len, mini, index_num);
	else if (input[start] == '>' && len == 1)
		mini = ft_get_redi_out(input, start, len, mini, index_num);
	return (mini);
}

t_minishell	*ft_add_new_node(char *input, int start, int len,
	t_minishell *mini, int *index_num)
{
	char	*sub_str;
	t_list	*new;

	sub_str = ft_substr(input, start, len);
	new = ft_lstnew(sub_str);
	ft_lstadd_back(&mini->nodes_t, new);
	new->index = *index_num;
	new->content = malloc((ft_strlen(sub_str) + 1) * sizeof(char));
	ft_strlcpy(new->content, sub_str, ft_strlen(sub_str) + 1);
	free(sub_str);
	*index_num = *index_num + 1;
	return (mini);
}

t_minishell	*ft_get_redi_in(char *input, int start, int len,
	t_minishell *mini, int *index_num)
{
	char	*sub_str;
	t_list	*new;

	sub_str = ft_substr(input, start, len);
	new = ft_lstnew(sub_str);
	new->index = *index_num;
	ft_lstadd_back(&mini->nodes_t, new);
	new->content = malloc((ft_strlen(sub_str) + 1) * sizeof(char));
	ft_strlcpy(new->content, sub_str, ft_strlen(sub_str) + 1);
	free(sub_str);
	*index_num = *index_num + 1;
	return (mini);
}
