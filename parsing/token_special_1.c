/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_special_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasari <sebasari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:27:03 by sebasari          #+#    #+#             */
/*   Updated: 2024/09/19 15:46:02 by sebasari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*ft_get_redi_herodoc(char *input, int start, int len, t_minishell *mini, int *index_num)
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

t_minishell	*ft_get_redi_append(char *input, int start, int len, t_minishell *mini, int *index_num)
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

t_minishell	*ft_assign_special_type(t_minishell *mini)
{
	t_list	*tmp;
	char	*str;

	tmp = mini->nodes_t;
	while (tmp != NULL)
	{
		str = (char *)tmp->content;
		if (ft_controll_qoutes(str) == 1)
			tmp->type = STRING;
		else if (ft_strncmp(str, "|", 1) == 0)
			tmp->type = PIPE;
		else if (ft_strncmp(str, ">", 2) == 0)
			tmp->type = GREATER;
		else if (ft_strncmp(str, "<", 2) == 0)
			tmp->type = SMALLER;
		else if (ft_strncmp(str, ">>", 3) == 0)
			tmp->type = APPEND;
		else if (ft_strncmp(str, "<<", 3) == 0)
			tmp->type = HERE_DOC;
		else 
			tmp->type = STRING;
		tmp = tmp->next;
	}
	return (mini);
}

t_minishell	*ft_get_redi_out(char *input, int start, int len, t_minishell *mini, int *index_num)
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

t_minishell	*ft_get_pipe(char *input, int start, int len, t_minishell *mini, int *index_num)
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