/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 20:05:54 by user42            #+#    #+#             */
/*   Updated: 2021/01/29 20:15:42 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINISHELL_H
# define _MINISHELL_H
# include "../libft/libft.h"
# include <dirent.h>
# include <stdio.h>
# include <wait.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# define WRITE_SIDE 1
# define READ_SIDE 0

typedef	struct	s_tuples
{
	char	*type;
	char	*content;
	int		last;
}				t_tuples;

typedef	struct	s_pipes
{
	int	pipe_needed;
	int	pipe_full;
	int	saved_stdin;
	int	new_pipe[2];
	int	old_pipe[2];
	int	saved_std;
	int	redir_fd;
	int	redir_eta;
}				t_pipes;

typedef struct	s_parser
{
	char		**args;
	char		**args_spaced;
	char		*bin_path;
	t_tuples	*token_list;
	int			was_backslash;
	long long	exit_value;
}				t_parser;

char			**g_mini_env;
int				g_ret;
int				g_old_ret;
int				export_builtin(char **args, char **mini_env[]);
void			env_builtin(char *mini_env[]);
int				unset_builtin(char *env_remove, char **mini_env[]);
int				echo_builtin(char **av);
int				ft_echo_first_arg(char **av, int *n_option, int av_space);
char			**cpy_env(char **env);
void			indent_shlvl(char	**mini_env[]);
void			edit_env_var(char *var, char **mini_env[]);
char			*get_var_value(char *name, char *env[]);
int				pwd_builtin(char *mini_env[]);
char			**parse_path(char *name, char *env[]);
char			*find_command(char *command, char *dir);
char			*find_path(char *command, char **mini_env);
char			*get_user_line(char *mini_env[]);
int				exec_single_command
(t_parser *parser, t_pipes *pipes, char **mini_env[]);
char			**cd_builtin(char **args, char **mini_env[]);
int				exit_builtin(t_parser *parser);
void			print_mini_env(char **mini_env);
t_tuples		*lexer(char *line);
t_tuples		*realloc_tuples(t_tuples *old_token_list, t_tuples new_token);
t_tuples		*string_interpreter(t_tuples *token_list, char **mini_env[]);
int				token_list_len(t_tuples *token_list);
void			free_token_list(t_tuples *token_list);
int				parser(t_tuples *token_list, int *ret);
t_tuples		*string_interpreter(t_tuples *token_list, char **mini_env[]);
int				special_char_tuple(int i, char *line, t_tuples **token_list);
int				var_tuple(int i, char *line, t_tuples **token_list);
int				command_tuple(int i, char *line, t_tuples **token_list);
int				path_tuple(int i, char *line, t_tuples **token_list);
int				strong_string_tuple(int i, char *line, t_tuples **token_list);
int				is_special_char(char c);
int				exist_path(char *path);
int				command_exist(t_parser *parser, char **mini_env[]);
int				is_builtin(char *command);
int				exec_builtin(t_parser *parser, char **mini_env[]);
int				is_delimiter(char c);
int				failed_exec(int error_no);
int				return_values(int status);
int				is_special_char(char c);
int				is_regular_directory(const char *path);
int				is_regular_file(const char *path);
int				redirection(t_parser *parser, t_pipes *pipes);
int				need_redirect(t_parser *parser);
void			reset_fd(t_pipes *pipes);
int				need_redirect(t_parser *parser);
int				check_synthax(t_parser *parser);
void			display_error(char *path);

#endif
