/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 00:32:55 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/28 13:08:24 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// signal handler for parent process
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

// handle ctrl c
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
