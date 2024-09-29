/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:07:13 by sebasari          #+#    #+#             */
/*   Updated: 2024/09/29 16:26:20 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_fd
{
	int			out;
	int			in;
	struct s_fd	*next;
}				t_fd;

typedef struct s_file
{
	char			*after;
	int				type;
	struct s_file	*next;
}				t_file;

typedef struct s_parse
{
	char			**args;
	int				out_file;
	int				in_file;
	struct s_parse	*next;
	t_file			*file;
}				t_parse;

typedef struct s_minishell
{
	t_list		*nodes_t;
	t_parse		*nodes_p;
	t_fd		*fd;
	t_file		*file;
	int			token_num;
	int			token_num2;
	int			in;
	int			in2;
	int			out;
	int			out2;
	char		**envp;
	char		*str;
	int			exit_status;
	int			error;
	int			pipe_flag;
	int			flag2;
	char		*old_pwd;
	char		**paths;
	char		**input;
}				t_minishell;

int			check_if_empty(char *str);
void		adjsut_all(char *input);
int			ft_single_quotes_finised(char *input, int index);
int			ft_quotes_num(char *input, char c);
int			ft_is_quotes_there(char *input);
int			ft_is_quotes_there_index(char c);
int			ft_quotes(char *input);
int			ft_last_index_check(char *str);
int			ft_double_quotes_check(char *str, int index);
int			ft_double_quotes_finised(char *input, int index);
int			ft_even_odd(char *str, char c);
t_list		*add_q_to_nodes(int *index, char *input, t_list *mini_list);
int			ft_find_next_q(int start, char *input);
t_list		*ft_getridof_q(t_list *nodes_t);
t_list		*ft_basic_q(t_list *nodes_t, int len);
int			parse_init(char *input);
t_minishell	*ft_tokanazition(char **str, t_minishell *mini);
int			ft_control_token(t_minishell *mini);
char		*double_quotes_dollar(char **env, char *input);
t_minishell	*parse(int in_file, int out_file, t_minishell *mini);
t_parse		*init_cmd(int in_file, int out_file);
void		add_new_node(t_parse *current, t_parse **list);
void		handle_pipes(t_list **token, t_parse **old_current);
void		adjust_redirecs(t_list **token, t_parse **current);
void		add_arguments(t_list **token, t_parse **current);
t_minishell	*create_out_dup_list(t_minishell *mini);
char		*ft_envp_var(char *envp, int i);
char		*ft_check_envp_exit_stat(char *str, int *i);
char		*ft_handle_envp_var(char **envp, char *str, int *i);
char		*ft_check_string(char *str, int *i);
char		**ft_search_envp_vars(char **str);
int			ft_lstprint_t(t_minishell *mini);
int			ft_get_size_double_point(char **str);
void		ft_split_free(char **str);
void		del(void *content);
int			ft_strlen_adjusted(char **str);
char		*ft_strtok(char *str, char *delim);
char		*ft_tab_to_space(char *input);
void		print_error(char *arg, char *message, int exit_status);
t_minishell	*ft_delete_first_node(t_minishell *mini);
int			ft_controll_qoutes(char *str);
int			ft_updated_strchr(char *str, int c);
void		ft_init(char **envp);
char		**ft_store_envp(char **envp);
void		ft_modify_string(char **old, char **new);
int			ft_is_exited(int status);
int			ft_get_exit_status(int status);
char		**ft_split_adjusted(char *s, char c);
int			check_for_q(t_minishell *mini);
char		*ft_handle_q(char **s);
int			ft_token_counter(char **str);
void		print_char_array(char **array);
char		*ft_custom_getenv(char *name);
char		*ft_str_join2(char *str);
void		ft_update_path_dir(void);
char		*ft_strjoin_free(char const *s1, char const *s2);
char		*ft_char_string(char c);
void		ft_ignore_signals(void);
void		ft_heredoc_signal_init(int sig);
void		ft_ctrl_c(int signal);
void		ft_ctrl_d(char *str);
void		ft_sigint_handler(int signum);
int			ft_special_type_index(char c);
int			ft_special_type(char *input);
t_minishell	*ft_find_the_type(char *input, int start, int len,
				t_minishell *special, int *index_num);
t_minishell	*ft_get_redi_in(char *input, int start, int len,
				t_minishell *special, int *index_num);
t_minishell	*ft_get_redi_out(char *input, int start, int len,
				t_minishell *special, int *index_num);
t_minishell	*ft_get_pipe(char *input, int start, int len,
				t_minishell *mini, int *index_num);
t_minishell	*ft_get_redi_herodoc(char *input, int start, int len,
				t_minishell *special, int *index_num);
t_minishell	*ft_get_redi_append(char *input, int start, int len,
				t_minishell *special, int *index_num);
t_minishell	*ft_assign_special_type(t_minishell *mini);
t_minishell	*divide_accordingly(char *input, t_minishell *mini, int *index);
t_minishell	*ft_add_new_node(char *input, int start, int len,
				t_minishell *mini, int *index_num);
int			ft_syntax_check(t_minishell *mini);
int			fixed_check(t_list *tmp_token);
int			redic_check(t_list *tmp_token);
int			pipe_check(t_list *tmp_token, t_list *tmp_prev);
void		ft_execute_commands(t_parse *parse, t_file *file, t_fd **fd);
void		ft_execve_or_builtin(char **str);
void		ft_dup_fd(t_parse *parse);
void		ft_command(t_parse *parse, t_fd **fd);
int			ft_builtin_or_not(char *str);
void		ft_execute_builtins(char **commands);
void		ft_execution(t_minishell *mini);
void		ft_execve_or_builtin(char **str);
void		ft_write_heredoc(char *str, int pipe_fd);
void		ft_process_heredoc_data(char **envp, char *str,
				int pipe_fd, t_file **file);
void		ft_heredoc_parent_process(int pipe_fd[2], t_parse *parse,
				t_file **file, t_fd **fd);
void		ft_heredoc(t_parse *parse, t_file **file, t_fd **fd);
void		ft_check_next_node(t_parse *parse, t_file **file);
char		*ft_convert_char_to_string(char c);
char		*ft_add_char_to_string(char *str, char c);
char		*ft_search_and_expand_env(char **env, char *str);
void		ft_return_fd(void);
void		ft_free_open_pipes(int **fd_pipe);
int			**ft_open_pipe(void);
void		ft_write_pipe(t_parse *parse, int **fd_pipe, int i, t_fd **fd);
void		ft_connect_pipes(t_parse *parse, int **fd_pipe, int i);
void		ft_handle_pipe(t_parse *parse, t_fd **fd);
void		ft_execute(char *full_path, char **str);
char		*ft_search_path(char *str, char *path);
char		*ft_my_get_env(char **envp, char *str);
int			ft_check_if_path(char *str);
void		ft_execute_execve(char **str);
void		ft_append(t_parse *parse, t_file **file);
void		ft_redirect_out(t_parse *parse, t_file **file);
void		ft_redirect_in(t_parse *parse, t_file **file);
void		ft_cd(char **str);
bool		ft_check_option_n(char *str, int i);
int			ft_check_option(char *str);
void		ft_echo(char **str);
void		ft_env(char	**input);
void		ft_exit(char **str);
int			ft_check_envp_var(char *str);
int			ft_check_equal_sign(char *str);
void		ft_display_env(char *str);
void		ft_print_envp(void);
void		ft_print_single(char *str);
int			ft_is_exist(char *str);
int			ft_number_of_envp_var(void);
void		ft_free_array(char **str);
void		ft_add_new_env(char *str);
void		ft_export(char **input);
void		ft_pwd(void);
void		ft_remove_var(char *str);
void		ft_unset(char **input);
void		ft_print(char **str, int i, int flag);
void		free_token(t_list *token);
void		free_file(t_file *file);
void		free_parse(t_parse *parse);
void		free_fd(t_fd *fd);
void		free_all(char *str);
void		clean_the_mess(void);

extern t_minishell	g_minishell;

#endif
