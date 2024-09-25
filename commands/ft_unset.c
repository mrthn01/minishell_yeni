/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:58:28 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/21 15:48:45 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// unset (removing environment elements)
void	ft_remove_var(char *str)
{
	char	**updated_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	updated_env = ft_calloc(sizeof(char *), ft_number_of_envp_var() + 1);
	while (g_minishell.envp[i])
	{
		if (ft_strncmp(g_minishell.envp[i], str, ft_strlen(str)))
		{
			updated_env[j] = ft_strdup(g_minishell.envp[i]);
			j++;
		}
		i++;
	}
	updated_env[j] = NULL;
	ft_free_array(g_minishell.envp);
	g_minishell.envp = updated_env;
}

void	ft_unset(char **input)
{
	char	*str;

	input++;
	while (*input)
	{
		str = ft_strjoin(*input, "=");
		ft_remove_var(str);
		free(str);
		input++;
	}
}
