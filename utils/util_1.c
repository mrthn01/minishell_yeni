/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:08:44 by sebasari          #+#    #+#             */
/*   Updated: 2024/09/29 15:55:54 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_split_free(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}

int	ft_lstprint_t(t_minishell *mini)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = mini->nodes_t;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int	ft_get_size_double_point(char **str)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (str[i])
	{
		size += ft_strlen(str[i]);
		i++;
	}
	return (size);
}

void	print_error(char *arg, char *message, int exit_status)
{
	char	*str;

	str = ft_strjoin(arg, message);
	ft_putstr_fd(str, 2);
	free(str);
	g_minishell.exit_status = exit_status;
}

int	ft_find_starting_index_of_q(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_is_quotes_there_index(str[i]))
			return (i);
		i++;
	}
	return (0);
}
