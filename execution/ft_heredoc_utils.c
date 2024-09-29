/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:57:07 by melcuman          #+#    #+#             */
/*   Updated: 2024/09/29 17:57:08 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_next_node(t_parse *parse, t_file **file)
{
	if ((*file)->next != NULL)
	{
		*file = (*file)->next;
		return ;
	}
	else if (parse->args[0])
	{
		(*file) = (*file)->next;
		ft_execve_or_builtin(parse->args);
	}
}

char	*ft_convert_char_to_string(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*ft_add_char_to_string(char *str, char c)
{
	char	*new_str;
	char	*str_c;

	str_c = ft_convert_char_to_string(c);
	new_str = ft_strjoin(str, str_c);
	str = ft_strdup(new_str);
	free(new_str);
	free(str_c);
	return (str);
}

char	*ft_search_and_expand_env(char **env, char *str)
{
	char	*temp;
	char	*var;
	int		i;

	temp = ft_calloc(1, sizeof(char));
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			var = ft_handle_envp_var(env, str, &i);
			temp = ft_strjoin(temp, var);
			free(var);
		}
		if (str[i] == '\0')
			break ;
		if (str[i] == '$')
			continue ;
		temp = ft_add_char_to_string(temp, str[i]);
		i++;
	}
	return (temp);
}
