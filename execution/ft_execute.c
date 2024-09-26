/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:20:49 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/26 18:49:27 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

void	ft_execute_commands(t_parse *parse, t_file *file, t_fd **fd)
{
	if (file == NULL)
	{
		ft_execve_or_builtin(parse->args);
		if (g_minishell.token_num2)
			ft_return_fd();
		else
			dup2(parse->in_file, STDIN_FILENO);
		return ;
	}
	while (file != NULL)
	{
		if (file->type == GREATER)
			ft_redirect_in(parse, &file);
		else if (file->type == SMALLER)
			ft_redirect_out(parse, &file);
		else if (file->type == APPEND)
			ft_append(parse, &file);
		else if (file->type == HERE_DOC)
			{
				printf("Geldi gene\n");
				ft_heredoc(parse, &file, fd);
			}
		if (file == NULL && parse->next == NULL)
			ft_return_fd();
	}
}

void	ft_execve_or_builtin(char **str)
{
	pid_t	pid;
	int		type;

	type = ft_builtin_or_not(str[0]);
	if (g_minishell.token_num2 == 1 && type != 0)
	{
		ft_execute_builtins(str);
		return ;
	}
	// signal();
	pid = fork();
	if (pid == 0)
	{
		if (type != 0)
		{
			ft_execute_builtins(str);
			exit(0);
		}
		else
			ft_execute_execve(str);
	}
	return ;
}

void	ft_command(t_parse *parse, t_fd **fd)
{
	int		type; // sinyal kısmıyla alakalı

	type = ft_builtin_or_not(parse->args[0]); // bu kısımda sinyallerle ilgili //
	g_minishell.pipe_flag = 0;
	if (parse->next != NULL)
	{
		g_minishell.pipe_flag = 1;
		ft_handle_pipe(parse, fd);
	}
	else
		ft_execute_commands(parse, parse->file, fd);
	while (waitpid(0, &g_minishell.exit_status, 0) > 0)
		continue;
	if (type == 0)
	{
		if (ft_is_exited(g_minishell.exit_status))
			g_minishell.exit_status = ft_get_exit_status(g_minishell.exit_status);
		else
			g_minishell.exit_status = 130;
	}
	signal(SIGQUIT, SIG_IGN);
}

void	ft_dup_fd(t_parse *parse)
{
	if (parse->args[0])
	{
		parse->in_file = dup(g_minishell.in);
		parse->out_file = dup(g_minishell.in);
	}
	g_minishell.in = dup(STDIN_FILENO);
	g_minishell.in2 = dup(STDIN_FILENO);
	g_minishell.out = dup(STDOUT_FILENO);
	g_minishell.out2 = dup(STDOUT_FILENO);
}

void	ft_execution(t_minishell *mini)
{
	t_parse	*parse;
	t_fd	*fd;
	char	*str;

	parse = mini->nodes_p;
	str = (char *)mini->nodes_t->content;
	if (mini->nodes_t == NULL || str == NULL)
		return ;
	ft_dup_fd(parse);
	ft_command(parse, &fd);
}
