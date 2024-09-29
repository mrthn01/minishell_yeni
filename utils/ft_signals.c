/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:48:04 by melcuman          #+#    #+#             */
/*   Updated: 2024/09/29 18:12:35 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

void	ft_ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
}

void	ft_heredoc_signal_init(int sig)
{
	(void)sig;
	printf("\n");
	g_minishell.exit_status = 130;
	free_all(g_minishell.str);
	clean_the_mess();
	exit(g_minishell.exit_status);
}

void	ft_ctrl_c(int signal)
{
	// rl_replace_line("", 0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
	g_minishell.exit_status = 128 + signal;
}

void	ft_ctrl_d(char *str)
{
	if (!str)
	{
		printf("\nexit\n");
		free_all(g_minishell.str);
		clean_the_mess();
		exit(g_minishell.exit_status);
	}
}

void	ft_sigint_handler(int signum)
{
	printf("\n");
	g_minishell.exit_status = 128 + signum;
}
