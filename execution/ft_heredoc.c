/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:31:01 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/27 16:53:05 by melcuman         ###   ########.fr       */
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
		if (ft_strncmp(str, (*file)->after, ft_strlen((*file)->after)) == 0)
		{
			break ;
		}
		str = ft_search_and_expand_env(envp, str);
		if ((*file)->type != HERE_DOC || (*file)->next == NULL)
			ft_write_heredoc(str, pipe_fd);
		free(str);
	}
}

// manage parent process for heredoc. !!! pipe_fd[0] refers to reading side of path, pipe_fd[1] is the writing side of pipe
void	ft_heredoc_parent_process(int pipe_fd[2], t_parse *parse, t_file **file, t_fd **fd)
{
	close(pipe_fd[1]);
	ft_ignore_signals();
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
		if (parse->args[0])
		{
			ft_execve_or_builtin(parse->args);
		}
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ft_ctrl_c);
}

// heredoc
void	ft_heredoc(t_parse *parse, t_file **file, t_fd **fd)
{
	int		p_fd[2];
	int		pid;
	char	**envp;
	char	*str;

	str = NULL;
	dup2((*fd)->out, STDOUT_FILENO);
	dup2((*fd)->in, STDIN_FILENO);
	envp = g_minishell.envp;
	pipe(p_fd);
	pid = fork();
	signal(SIGINT, &ft_heredoc_signal_init);
	if (pid == 0)
	{
		close(p_fd[0]);
		ft_process_heredoc_data(envp, str, p_fd[1], file);
		close(p_fd[1]);
		free_all(g_minishell.str);
		clean_the_mess();
		exit(0);
	}
	else
		ft_heredoc_parent_process(p_fd, parse, file, fd);
}
