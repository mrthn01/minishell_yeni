/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:20:49 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/25 20:53:22 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return entered values as array list
char	**ft_get_char(t_minishell *token)
{
	char	**argv;
	t_list	*temp;
	int		argc;
	int		i;
	
	temp = token->nodes_t;
	argc = 0;
	i = 0;
	while (temp)
	{
		argc++;
		temp = temp->next;
	}
	temp = token->nodes_t;
	argv = malloc((argc + 1) *  sizeof(char *));
	if (!argv)
		return (NULL);
	while (i < argc && temp != NULL)
	{
		argv[i] = (char *)temp->content;
		temp = temp->next;
		i++;
	}
	argv[argc] = NULL;
	return (argv);
}

char	*ft_find_command_path(char *command)
{
    char		*path;
	char		*paths;
	char		*dir;
	static char	full_path[1024];
    // getenv -> set, unset, and fetch environment variables from the host environment list
    // return value of getenv: The getenv() function returns the value of the environment variable as a NUL-terminated
    // string.  If the variable name is not in the current environment, NULL is returned.
    path = getenv("PATH");
	if (!path)
		return (NULL);
	paths = ft_strdup(path);
	dir = strtok(paths, ":"); // ft_strtok hatalı
	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(paths);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}
	free(paths);
	return (NULL);
}

// void	ft_execute_execve(char *str)
// {
// 	char	**argv;
// 	char	*command_path;
// 	char	*str;
// 	int		argc;
// 	int		i;
// 	t_list	*temp;
	
// 	temp = mini->nodes_t;
// 	str = (char *)temp->content;
// 	if (mini == NULL || str == NULL)
// 		return ;
// 	command_path = ft_find_command_path(str);
// 	if (command_path == NULL)
// 	{
// 		printf("%s: command not found\n", str);
// 		return ;
// 	}
// 	argc = 0;
// 	while (temp)
// 	{
// 		argc++;
// 		temp = temp->next;
// 	}
// 	argv = malloc((argc + 1) *  sizeof(char *));
// 	i = 0;
// 	temp = mini->nodes_t;
// 	while (i < argc && temp != NULL)
// 	{
// 		argv[i] = (char *)temp->content;
// 		temp = temp->next;
// 		i++;
// 	}
// 	argv[argc] = NULL; // last char shoudl be null
// 	if (execve(command_path, argv, NULL) == -1)
// 	{
// 		perror("execve failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	free(argv);
// }

// void	ft_builtin_commands(t_minishell *mini)
// {
// 	char	**input;

// 	input = ft_get_char(mini);
// 	if (ft_strncmp(input[0], "pwd", ft_strlen(str)) == 0)
// 		ft_pwd(*input);
// 	else if (ft_strncmp(input[0], "echo", ft_strlen(str)) == 0)
// 		ft_echo(input);
// 	else if (ft_strncmp(input[0], "cd", ft_strlen("cd")) == 0)
// 		ft_cd(input);
// 	else if (ft_strncmp(input[0], "env", ft_strlen("env")) == 0)
// 		ft_env(input);
// 	else if (ft_strncmp(input[0], "export", ft_strlen("export")) == 0)
// 		ft_export(input);
// 	else if (ft_strncmp(input[0], "unset", ft_strlen("unset")) == 0)
// 		ft_unset(input);
// 	else if (ft_strncmp(input[0], "exit", ft_strlen(str)) == 0)
// 		ft_exit(input);
// }

void	ft_execute_commands(t_parse *parse, t_file *file, t_fd **fd, int flag)
{
	if (file == NULL)
	{
		ft_execve_or_builtin(parse->args, flag);
		if (flag == 0)
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
			ft_heredoc(parse, &file, fd, flag);
		if (file == NULL && parse->next == NULL)
			ft_return_fd();
	}
}

void	ft_execve_or_builtin(char **str, int flag)
{
	pid_t	pid;
	int		type;

	type = ft_builtin_or_not(str[0]);
	printf("type: %d and flag: %d\n", type, flag);
	if (type != 0)
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
			ft_execute_execve(str, flag);
	}
	return ;
}

void	ft_command(t_parse **parse, t_fd **fd)
{
	int		type; // sinyal kısmıyla alakalı
	int		flag;

	type = ft_builtin_or_not(parse[0]->args[0]); // bu kısımda sinyallerle ilgili //
	flag = 0;
	if (parse[1] != NULL)
	{
		flag = 1;
		ft_handle_pipe(parse, fd, flag);
	}
	else
		ft_execute_commands(parse[0], parse[0]->file, fd, flag);
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
	t_parse	**parse;
	t_fd	*fd;
	char	*str;

	parse = &mini->nodes_p;
	str = (char *)mini->nodes_t->content;
	if (mini->nodes_t == NULL || str == NULL)
		return ;
	ft_dup_fd(parse[0]);
	ft_command(parse, &fd);
}
