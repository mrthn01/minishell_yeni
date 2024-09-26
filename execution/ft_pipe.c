/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:35:38 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/26 18:41:28 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_return_fd(void)
{
	dup2(g_minishell.out2, STDOUT_FILENO);
	close(g_minishell.out2);
	dup2(g_minishell.in2, STDIN_FILENO);
	close(g_minishell.in2);
}

// free open pipes
void	ft_free_open_pipes(int **fd_pipe)
{
	int	i;

	i = 0;
	while (fd_pipe[i])
	{
		free(fd_pipe[i]);
		i++;
	}
	free(fd_pipe);
}

int	**ft_open_pipe()
{
	int	**pipe_fd;
	int	i;
	int	j;

	i = (g_minishell.token_num2); // öylesine
	printf("pipe sayısy: %d \n", i);
	pipe_fd = ft_calloc(i + 1, sizeof(int *));
	j = 0;
	while (j < i)
	{
		pipe_fd[j] = malloc(sizeof(int) * 2);
		pipe(pipe_fd[j]);
		j++;
	}
	return (pipe_fd);
}

void	ft_write_pipe(t_parse *parse, int **fd_pipe, int i, t_fd **fd)
{
	if (parse->next == NULL)
	{
		dup2(g_minishell.out, STDOUT_FILENO);
		parse->out_file = g_minishell.out;
		close(g_minishell.out);
		close(fd_pipe[i - 1][0]);
		ft_execute_commands(parse, parse->file, fd);
		return ;
	}
	else
	{
		dup2(fd_pipe[i][1], STDOUT_FILENO);
		parse->out_file = fd_pipe[i][1];
		close(fd_pipe[i][1]);
		ft_execute_commands(parse, parse->file, fd);
	}
	if (i > 0)
		close(fd_pipe[i - 1][0]);
}

// connect pipes
void	ft_connect_pipes(t_parse *parse, int **fd_pipe, int i)
{
	(void)parse;
	if (parse == NULL)
	{
		dup2(g_minishell.in, STDIN_FILENO);
		close(g_minishell.in);
		return ;
	}
	if (i > 0)
	{
		dup2(fd_pipe[i - 1][0], STDIN_FILENO);
		parse->in_file = fd_pipe[i - 1][0];
	}
}

// handle pipe
void	ft_handle_pipe(t_parse *parse, t_fd **fd)
{
	int	i;
	int	**fd_pipe;

	i = 0;
	fd_pipe = ft_open_pipe();
	while (parse)
	{
		ft_write_pipe(parse, fd_pipe, i, fd);
		i++;
		parse = parse -> next;
		ft_connect_pipes(parse, fd_pipe, i);
	}
	ft_free_open_pipes(fd_pipe);
}
