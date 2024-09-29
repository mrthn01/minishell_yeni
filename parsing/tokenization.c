/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasari <sebasari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:04:05 by sebasari          #+#    #+#             */
/*   Updated: 2024/09/15 14:34:20 by sebasari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*double_quotes_dollar(char **env, char *input)
{
	char	*char_str;
	char	*new_str;
	char	*var;
	int		i;

	new_str = ft_strdup("");
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			var = ft_handle_envp_var(env, input, &i);
			if (var != NULL)
			{
				new_str = ft_strjoin_free(new_str, var);
				free(var);
			}
			continue ;
		}
		char_str = ft_char_string(input[i]);
		new_str = ft_strjoin_free(new_str, char_str);
		free(char_str);
		i++;
	}
	return (new_str);
}

int	ft_control_token(t_minishell *mini)
{
	int			i;
	char		*str;
	t_list		*tmp;

	if (check_for_q(mini) == 1)
	{
		print_error(NULL, "error: unifinished quotes\n", 2);
		return (1);
	}
	tmp = mini->nodes_t;
	while (tmp != NULL)
	{
		str = (char *)tmp->content;
		i = 0;
		while (str[i])
		{
			if (ft_is_quotes_there_index(str[i]) == 1)
				tmp = add_q_to_nodes(&i, str, tmp);
			if (ft_is_quotes_there_index(str[i]) == 2)
			{
				str = double_quotes_dollar(g_minishell.envp, str);
				if (tmp->content != NULL)
					free(tmp->content);
				tmp->content = str;
				tmp = add_q_to_nodes(&i, str, tmp);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	parse_init(char *input)
{
	char			**str;
	t_minishell		*mini;

	g_minishell.flag2 = 0;
	mini = malloc(sizeof(t_minishell));
	mini->nodes_t = malloc(sizeof(t_list));
	mini->nodes_t->next = NULL;
	input = ft_tab_to_space(input);
	str = ft_split_adjusted(input, ' ');
	str = ft_search_envp_vars(str);
	g_minishell.token_num2 = ft_token_counter(str);
	mini = ft_tokanazition(str, mini);
	g_minishell.nodes_t = mini->nodes_t;
	mini = ft_assign_special_type(mini);
	ft_control_token(mini);
	if (ft_control_token(mini) || ft_syntax_check(mini))
		return (1);
	g_minishell.token_num = ft_lstprint_t(mini);
	mini = parse(0, 1, mini);
	g_minishell.nodes_p = mini->nodes_p;
	ft_execution(mini);
	ft_free_array(str);
	free(mini);
	return (0);
}

t_minishell	*ft_tokanazition(char **str, t_minishell *mini)
{
	int		i;
	int		j;
	t_list	*new;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (ft_special_type(str[i]))
			mini = divide_accordingly(str[i], mini, &j);
		else
		{
			new = ft_lstnew(str[i]);
			ft_lstadd_back(&mini->nodes_t, new);
			new->index = j;
			new->content = malloc((ft_strlen(str[i]) + 1) * sizeof(char));
			ft_strlcpy(new->content, str[i], ft_strlen(str[i]) + 1);
			j++;
		}
		i++;
	}
	mini = ft_deleteFirstNode(mini);
	return (mini);
}
