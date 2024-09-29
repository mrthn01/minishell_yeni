/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:13:07 by sebasari          #+#    #+#             */
/*   Updated: 2024/09/29 16:02:58 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_adjusted(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	del(void *content)
{
	free(content);
}

char	*ft_strtok(char *str, char *delim)
{
	static char	*next;
	char		*mini_start;

	if (str != NULL)
		next = str;
	if (next == NULL)
		return (NULL);
	while (*next && ft_strchr(delim, *next))
		next++;
	if (*next == '\0')
		return (NULL);
	mini_start = next;
	while (*next && !ft_strchr(delim, *next))
		next++;
	if (*next)
	{
		*next = '\0';
		next++;
	}
	return (mini_start);
}

char	*ft_tab_to_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\t')
			input[i] = ' ';
		i++;
	}
	return (input);
}

t_minishell	*ft_delete_first_node(t_minishell *mini)
{
	t_list	*temp;

	temp = mini->nodes_t;
	if (!temp)
		return (NULL);
	mini->nodes_t = mini->nodes_t->next;
	free(temp);
	return (mini);
}
