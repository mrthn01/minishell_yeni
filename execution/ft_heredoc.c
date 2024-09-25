/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:31:01 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/25 21:01:16 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// write given string into pipe
void	ft_write_heredoc(char *str, int pipe_fd)
{
	int	len;

	len = ft_strlen(str);
	write(pipe_fd, str, len);
	write(pipe_fd, "\n", 1);
}

// get heredoc data and process it
void	ft_process_heredoc_data(char **envp, char *str, int pipe_fd, t_file **file)
{
	while (1)
	{
		str = readline("> ");
		if (str == 0)
		{
			print_error((*file)->after, ": Delimeter is not found\n", 0);
			free(str);
			break ;
		}
		if (strcmp(str, (*file)->after) == 0)
			break ;
		str = ft_search_and_expand_env(envp, str);
		if ((*file)->type != HERE_DOC || (*file)->after == NULL)
			ft_write_heredoc(str, pipe_fd);
		free(str);
	}
}

// manage parent process for heredoc. !!! pipe_fd[0] refers to reading side of path, pipe_fd[1] is the writing side of pipe
void	ft_heredoc_parent_process(int pipe_fd[2], t_parse *parse, t_file **file, t_fd **fd, int flag)
{
	close(pipe_fd[1]);
	// ignore any signals
	while (waitpid(0, &g_minishell.exit_status, 0) > 0)
		continue ;
	if (ft_is_exited(g_minishell.exit_status))
		g_minishell.exit_status = ft_get_exit_status(g_minishell.exit_status);
	dup2(parse->out_file, STDOUT_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	*fd = (*fd)->next;
	if ((*file)->next != NULL)
	{
		*file = (*file)->next;
		return ;
	}
	else
	{
		*file = (*file)->next;
		if (parse->args[0] != NULL)
			ft_execve_or_builtin(parse->args, flag);
	}
	// signal (SIGQUIT)
	// signal (SIGINT)
}

// heredoc
void	ft_heredoc(t_parse *parse, t_file **file, t_fd **fd, int flag)
{
	int		p_fd[2];
	int		pid;
	char	**envp;
	char	*str;

	str = NULL;
	envp = g_minishell.envp;
	dup2((*fd)->in, STDIN_FILENO);
	dup2((*fd)->out, STDOUT_FILENO);
	pipe(p_fd);
	pid = fork();
	// signal(SIGINT, &ft_heredoc_signal);
	if (pid == 0)
	{
		close(p_fd[0]);
		ft_process_heredoc_data(envp, str, p_fd[1], file);
		close(p_fd[1]);
		exit(0);
	}
	else
		ft_heredoc_parent_process(p_fd, parse, file, fd, flag);
}
