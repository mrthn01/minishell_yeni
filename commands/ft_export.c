/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:08:51 by melcuman          #+#    #+#             */
/*   Updated: 2024/09/27 15:56:34 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

// control env var
int	ft_check_envp_var(char *str)
{
	if (ft_isdigit(*str))
	{
		printf("error: export bad syntax\n");
		return (0);
	}
	return (1);
}

// check equal sign
int	ft_check_equal_sign(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=' || ft_isdigit(str[0]))
	{
		printf("error: export bad syntax\n");
		return (0);
	}
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0)
		{
			printf("error: export bad syntax\n");
			return (0);
		}
		i++;
	}
	if (str[i] != '=')
		return (1);
	else if (ft_updated_strchr(&str[i], '=') == 1)
		return (1);
	return (0);
}

void	ft_print_single(char *str)
{
	int	i;

	i = 0;
	printf("declare -x ");
	while (str[i] != '\0')
	{
		printf("%c", str[i]);
		i++;
	}
	printf("\n");
}

void	ft_print_envp()
{
	int	i;
	int	len;

	i = 0;
	while (g_minishell.envp[i])
	{
		len = ft_strlen(g_minishell.envp[i]);
		if (len == 1)
			ft_print_single(g_minishell.envp[i]);
		else
			ft_display_env(g_minishell.envp[i]);
		i++;
	}
}

// print env var
void	ft_display_env(char *str)
{
	int	i;

	i = 0;
	printf("describe -x ");
	while (str[i] != '=')
	{
		printf("%c", str[i]);
		i++;
	}
	printf("\"");
	while (str[i] != '\0')
	{
		printf("%c", str[i]);
		i++;
	}
	printf("\"\n");
}

// check env var in env var array. If it is exist return it is index, else return -1
int	ft_is_exist(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (g_minishell.envp[i])
	{
		j = 0;
		while (g_minishell.envp[i][j] && str[j])
		{
			if (str[j] == '=' && g_minishell.envp[i][j] == '=')
				return (i);
			if (str[j] != g_minishell.envp[i][j])
				break;
			j++;
		}
		i++;
	}
	return (-1);
}

// number of env var
int	ft_number_of_envp_var(void)
{
	int	i;

	i = 0;
	while (g_minishell.envp[i])
		i++;
	return (i);
}

void	ft_free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

// add new env variable to env array
void	ft_add_new_env(char *str)
{
	char	**new_var;
	int		i;

	i = 0;
	new_var = ft_calloc(sizeof(char *), ft_number_of_envp_var() + 2);
	if (!new_var)
		return ;
	while (g_minishell.envp[i])
	{
		new_var[i] = ft_strdup(g_minishell.envp[i]);
		i++;
	}
	new_var[i] = ft_strdup(str);
	ft_free_array(g_minishell.envp);
	g_minishell.envp = new_var;
}

// export command
void	ft_export(char **input)
{
	int	location;

	if (input[1] == NULL)
	{
		ft_print_envp();
		return ;
	}
	while (*++input)
	{
		if (ft_check_equal_sign(*input) == 0)
			continue ;
		if (*input && ft_check_envp_var(*input))
		{
			if (ft_is_exist(*input) != -1)
			{
				location = ft_is_exist(*input);
				free(g_minishell.envp[location]);
				g_minishell.envp[location] = ft_strdup(*input);
			}
			else
				ft_add_new_env(*input);
		}
	}
}
