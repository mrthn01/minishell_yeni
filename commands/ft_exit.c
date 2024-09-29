/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:04:11 by melcuman          #+#    #+#             */
/*   Updated: 2024/09/29 18:04:37 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exit_shell(int number_of_pipe)
{
	if (number_of_pipe == 1)
	{
		printf("exit\n");
		free_all(g_minishell.str);
		clean_the_mess();
		exit(g_minishell.exit_status);
	}
}

static int	ft_number_of_args(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_check_exit_args(char **str, int number_of_pipes)
{
	if (ft_number_of_args(str) > 2)
	{
		print_error(NULL, "exit\nexit: too many arguments\n", 1);
		if (number_of_pipes == 1)
		{
			free_all(g_minishell.str);
			clean_the_mess();
			exit(1);
		}
	}
	else
	{
		g_minishell.exit_status = ft_atoi(str[1]) % 256;
		if (number_of_pipes == 1)
		{
			free_all(g_minishell.str);
			clean_the_mess();
			exit(g_minishell.exit_status);
		}
	}
}

int	ft_number_option(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '+' || str[i] == '-')
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_exit(char **str)
{
	int		number_of_pipes;

	number_of_pipes = g_minishell.token_num2;
	if (ft_number_of_args(str) == 1)
		ft_exit_shell(number_of_pipes);
	else
	{
		if (ft_number_option(str[1]))
			ft_check_exit_args(str, number_of_pipes);
		else
		{
			print_error(NULL, "exit\nexit: numeric argument required\n", 2);
			if (number_of_pipes == 1)
			{
				free_all(g_minishell.str);
				clean_the_mess();
				exit(2);
			}
		}
	}
}
