/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:21:38 by melcuman          #+#    #+#             */
/*   Updated: 2024/09/27 10:56:19 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

// >> append
void	ft_append(t_parse *parse, t_file **file)
{
	int	fd_file;

	fd_file = open((*file)->after, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_file == -1)
	{
		print_error((*file)->after, ": No such file or directory", 0);
	}
	if ((*file)->next == NULL || (*file)->next->type != APPEND)
	{
		dup2(fd_file, STDOUT_FILENO);
		if ((*file)->next != NULL)
		{
			*file = (*file)->next;
			close(fd_file);
			return ;
		}
		else if (parse->args[0])
			ft_execve_or_builtin(parse->args);
	}
	close(fd_file);
	g_minishell.flag2 = 0;
	*file = (*file)->next;
}

// < redirect out
void	ft_redirect_out(t_parse *parse, t_file **file)
{
	int	fd_file;

	fd_file = open((*file)->after, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_file == -1)
	{
		print_error((*file)->after, ": No such file or directory", 0);
		g_minishell.flag2 = 1;
		*file = (*file)->next;
		return ;
	}
	if ((*file)->next == NULL || (*file)->next->type != SMALLER)
	{
		dup2(fd_file, STDIN_FILENO);
		if ((*file)->next != NULL)
		{
			*file = (*file)->next;
			close(fd_file);
		}
		else if (parse->args[0])
			ft_execve_or_builtin(parse->args);
	}
	close(fd_file);
	g_minishell.flag2 = 0;
	*file = (*file)->next;
}

// > redirect in
void	ft_redirect_in(t_parse *parse, t_file **file)
{
	int	fd_file;

	fd_file = open((*file)->after, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_file == -1)
		print_error((*file)->after, ": No such file or directory", 0);
	if ((*file)->next == NULL || (*file)->next->type != GREATER)
	{
		dup2(fd_file, STDOUT_FILENO);
		if ((*file)->next != NULL)
		{
			*file = (*file)->next;
			close(fd_file);
			return ;
		}
		else if (parse->args[0])
			ft_execve_or_builtin(parse->args);
	}
	close(fd_file);
	g_minishell.flag2 = 0;
	*file = (*file)->next;
}
