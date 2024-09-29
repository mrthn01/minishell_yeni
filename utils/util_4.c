/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:47:46 by melcuman          #+#    #+#             */
/*   Updated: 2024/09/29 16:08:36 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

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
			while (g_minishell.envp[i][j] != '=')
				j++;
			free(new_str);
			return (ft_strdup(&g_minishell.envp[i][j + 1]));
		}
		i++;
	}
	free(new_str);
	return (ft_calloc(sizeof(char *), 1));
}

void	ft_update_path_dir(void)
{
	char	*path;

	if (g_minishell.paths)
		ft_free_array(g_minishell.paths);
	path = getenv("PATH");
	if (!(*path))
	{
		g_minishell.paths = 0;
	}
	else
		g_minishell.paths = ft_split(path, ':');
}

char	*ft_char_string(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	int		i;
	int		a;
	char	*str;

	if (!s1)
		return (0);
	i = ft_strlen(s1);
	a = ft_strlen(s2);
	str = malloc((a + i) * sizeof(char) + 1);
	if (!str)
		return (0);
	i = 0;
	a = 0;
	while (s1[i])
		str[a++] = s1[i++];
	i = 0;
	while (s2[i])
		str[a++] = s2[i++];
	str[a] = '\0';
	free((char *)s1);
	return (str);
}

void	ft_modify_string(char **old, char **new)
{
	free(*old);
	*old = ft_strdup(*new);
	free(*new);
}
