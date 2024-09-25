/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 22:20:12 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/24 16:08:43 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

// getenv functions but customized version
char	*ft_custom_getenv(char *name)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = ft_strjoin(name, "=");
	while (g_minishell.envp[i])
	{
		if (ft_strncmp(g_minishell.envp[i], new_str, ft_strlen(new_str)) == 0)
		{
			while(g_minishell.envp[i][j] != '=')
				j++;
			free(new_str);
			return (ft_strdup(g_minishell.envp[i][j + 1]));
		}
		i++;
	}
	free(new_str);
	return (ft_calloc(sizeof(char *), 1));
}

// void	ft_update_path(void)
// {
// 	char	*path;

// 	if (g_minishell.)
// }
