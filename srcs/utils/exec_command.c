/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:56:42 by user42            #+#    #+#             */
/*   Updated: 2021/01/29 19:38:19 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		no_pipes(t_parser *parser, char **mini_env[])
{
	int pid;
	int status;

	if (is_builtin(parser->args[0]) == 1)
		return (exec_builtin(parser, mini_env));
	if ((pid = fork()) == 0)
	{
		execve(parser->bin_path, parser->args, *mini_env);
		exit(failed_exec(errno));
	}
	else
	{
		waitpid(pid, &status, 0);
		return (return_values(status));
	}
	return (-1);
}

int		enter_pipe(t_parser *parser, t_pipes *pipes, char **mini_env[])
{
	int pid;
	int status;

	pipes->pipe_needed = 0;
	pipes->pipe_full = 1;
	pipe(pipes->new_pipe);
	if ((pid = fork()) == 0)
	{
		close(pipes->new_pipe[READ_SIDE]);
		dup2(pipes->new_pipe[WRITE_SIDE], STDOUT_FILENO);
		close(pipes->new_pipe[WRITE_SIDE]);
		if (is_builtin(parser->args[0]) == 1)
		{
			exec_builtin(parser, mini_env);
			exit(1);
		}
		execve(parser->bin_path, parser->args, *mini_env);
		exit(failed_exec(errno));
	}
	else
	{
		waitpid(pid, &status, 0);
		return (return_values(status));
	}
	return (-1);
}

int		pipe_output(t_parser *parser, t_pipes *pipes, char **mini_env[])
{
	int pid;
	int status;
	int ret;

	pipes->saved_stdin = dup(STDIN_FILENO);
	pipes->pipe_full = 0;
	close(pipes->old_pipe[WRITE_SIDE]);
	dup2(pipes->old_pipe[READ_SIDE], STDIN_FILENO);
	close(pipes->old_pipe[READ_SIDE]);
	if (is_builtin(parser->args[0]) == 1)
	{
		ret = exec_builtin(parser, mini_env);
		dup2(pipes->saved_stdin, STDIN_FILENO);
		close(pipes->saved_stdin);
		return (ret);
	}
	if ((pid = fork()) == 0)
	{
		execve(parser->bin_path, parser->args, *mini_env);
		exit(failed_exec(errno));
	}
	waitpid(pid, &status, 0);
	dup2(pipes->saved_stdin, STDIN_FILENO);
	close(pipes->saved_stdin);
	return (return_values(status));
}

int		double_pipes(t_parser *parser, t_pipes *pipes, char **mini_env[])
{
	int pid;
	int status;

	pipes->pipe_needed = 0;
	pipes->saved_stdin = dup(STDIN_FILENO);
	close(pipes->old_pipe[WRITE_SIDE]);
	dup2(pipes->old_pipe[READ_SIDE], STDIN_FILENO);
	close(pipes->old_pipe[READ_SIDE]);
	pipe(pipes->new_pipe);
	if ((pid = fork()) == 0)
	{
		close(pipes->new_pipe[READ_SIDE]);
		dup2(pipes->new_pipe[WRITE_SIDE], STDOUT_FILENO);
		close(pipes->new_pipe[WRITE_SIDE]);
		if (is_builtin(parser->args[0]) == 1)
			exec_builtin(parser, mini_env);
		if (is_builtin(parser->args[0]) == 1)
			exit(0);
		execve(parser->bin_path, parser->args, *mini_env);
		exit(failed_exec(errno));
	}
	waitpid(pid, &status, 0);
	dup2(pipes->saved_stdin, STDIN_FILENO);
	close(pipes->saved_stdin);
	return (return_values(status));
}

int		exec_single_command(t_parser *parser, t_pipes *pipes, char **mini_env[])
{
	int ret;

	pipes->redir_eta = 0;
	if (command_exist(parser, mini_env) == -1)
		return (127);
	if (ft_strcmp("exit", parser->args[0]) == 0)
		return (exit_builtin(parser));
	if (need_redirect(parser))
	{
		if (redirection(parser, pipes) != 0)
			return (1);
	}
	if (pipes->pipe_needed == 1 || pipes->pipe_full == 1)
		ft_memcpy(pipes->old_pipe, pipes->new_pipe, sizeof(pipes->new_pipe));
	if (pipes->pipe_needed == 1 && pipes->pipe_full == 1)
		ret = double_pipes(parser, pipes, mini_env);
	else if (pipes->pipe_needed == 1)
		ret = enter_pipe(parser, pipes, mini_env);
	else if (pipes->pipe_full == 1)
		ret = pipe_output(parser, pipes, mini_env);
	else
		ret = no_pipes(parser, mini_env);
	if (need_redirect(parser) == 0)
		reset_fd(pipes);
	return (ret);
}
