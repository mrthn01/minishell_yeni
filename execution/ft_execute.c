/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:20:49 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/25 23:34:17 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

// // return entered values as array list
// char	**ft_get_char(t_minishell *token)
// {
// 	char	**argv;
// 	t_list	*temp;
// 	int		argc;
// 	int		i;
	
// 	temp = token->nodes_t;
// 	argc = 0;
// 	i = 0;
// 	while (temp)
// 	{
// 		argc++;
// 		temp = temp->next;
// 	}
// 	temp = token->nodes_t;
// 	argv = malloc((argc + 1) *  sizeof(char *));
// 	if (!argv)
// 		return (NULL);
// 	while (i < argc && temp != NULL)
// 	{
// 		argv[i] = (char *)temp->content;
// 		temp = temp->next;
// 		i++;
// 	}
// 	argv[argc] = NULL;
// 	return (argv);
// }

// char	*ft_find_command_path(char *command)
// {
//     char		*path;
// 	char		*paths;
// 	char		*dir;
// 	static char	full_path[1024];
//     // getenv -> set, unset, and fetch environment variables from the host environment list
//     // return value of getenv: The getenv() function returns the value of the environment variable as a NUL-terminated
//     // string.  If the variable name is not in the current environment, NULL is returned.
//     path = getenv("PATH");
// 	if (!path)
// 		return (NULL);
// 	paths = ft_strdup(path);
// 	dir = strtok(paths, ":"); // ft_strtok hatalı
// 	while (dir != NULL)
// 	{
// 		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
// 		if (access(full_path, X_OK) == 0)
// 		{
// 			free(paths);
// 			return (full_path);
// 		}
// 		dir = strtok(NULL, ":");
// 	}
// 	free(paths);
// 	return (NULL);
// }

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
			; // redirect in
		else if (file->type == SMALLER)
			; // redirect out
		else if (file->type == APPEND)
			; // append
		else if (file->type == HERE_DOC)
			ft_heredoc(parse, &file, fd);
		if (file == NULL && parse->next == NULL)
			ft_return_fd();
	}
}

void	ft_execve_or_builtin(char **str)
{
	pid_t	pid;
	int		type;

	type = ft_builtin_or_not(str[0]);
	printf("type: %d\n", type);
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
	printf("%d \n", type);
	g_minishell.pipe_flag = 1;
	if (parse->next != NULL)
	{
		printf("GİRDİ\n");
		g_minishell.pipe_flag = 1;
		ft_handle_pipe(&parse, fd);
	}
	else
		ft_execute_commands(parse, parse->file, fd);
	// handle signals later //
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
