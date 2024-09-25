/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:06:14 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/25 19:43:47 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check for node. if there is node go to next node. If there isn't a node but there is a command execute command
void	ft_check_next_node(t_parse *parse, t_file **file, int flag)
{
	if ((*file)->next != NULL) // if there is a next file
	{
		*file = (*file)->next; // go to next file
		return ;
	}
	else if (parse->args[0]) // if it is an command
	{
		(*file) = (*file)->next;
		ft_execve_or_builtin(parse->args, flag);
	}
}

// conver char to string
char	*ft_convert_char_to_string(char c)
{
	char	*str;

	str = malloc(sizeof(char) *  2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return  (str);
}

// Add new character to already exist string
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

// extends environment variable inside of heredoc
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
			continue;
		temp = ft_add_char_to_string(temp, str[i]);
		i++;
	}
	return (temp);
}
