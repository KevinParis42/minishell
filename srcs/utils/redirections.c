/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 23:03:11 by kevin             #+#    #+#             */
/*   Updated: 2021/01/29 19:40:21 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_fd(t_pipes *pipes)
{
	if (pipes->redir_eta == 1)
	{
		close(pipes->redir_fd);
		dup2(pipes->saved_std, STDOUT_FILENO);
	}
	else if (pipes->redir_eta == 2)
		dup2(pipes->saved_std, STDIN_FILENO);
}

void	clean_args(t_parser *parser)
{
	int		i;

	i = -1;
	while (++i < ft_str_tab_len(parser->args_spaced))
	{
		while (i < ft_str_tab_len(parser->args))
		{
			if (ft_strcmp(parser->args_spaced[i], ">") == 0 ||
				ft_strcmp(parser->args_spaced[i], "<") == 0)
				parser->args_spaced = ft_pop_char_tab(parser->args_spaced,
					parser->args_spaced[i--]);
			if (ft_strcmp(parser->args[i], ">") == 0 ||
				ft_strcmp(parser->args[i], "<") == 0)
				parser->args = ft_pop_char_tab(parser->args, parser->args[i--]);
			i++;
		}
		if (ft_strcmp(parser->args_spaced[i], ">") == 0 ||
			ft_strcmp(parser->args_spaced[i], "<") == 0)
			parser->args_spaced = ft_pop_char_tab(parser->args_spaced,
				parser->args_spaced[i--]);
	}
	parser->args_spaced = ft_pop_char_tab(parser->args_spaced,
		parser->args[ft_str_tab_len(parser->args) - 1]);
	parser->args = ft_pop_char_tab(parser->args,
		parser->args[ft_str_tab_len(parser->args) - 1]);
}

void	redirect_stdout(t_parser *parser, t_pipes *pipes, int i)
{
	if (ft_strcmp(">", parser->args[i + 1]) == 0)
	{
		pipes->saved_std = dup(STDOUT_FILENO);
		pipes->redir_fd = open(
			parser->args[ft_str_tab_len(parser->args) - 1],
			O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		dup2(pipes->redir_fd, STDOUT_FILENO);
		pipes->redir_eta = 1;
		clean_args(parser);
	}
	else
	{
		pipes->saved_std = dup(STDOUT_FILENO);
		pipes->redir_fd = open(
			parser->args[ft_str_tab_len(parser->args) - 1],
			O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		dup2(pipes->redir_fd, STDOUT_FILENO);
		pipes->redir_eta = 1;
		clean_args(parser);
	}
}

int		redirect_stdin(t_parser *parser, t_pipes *pipes)
{
	struct stat	file_stat;
	char		*path;

	if (stat(parser->args[ft_str_tab_len(parser->args) - 1],
		&file_stat) < 0)
	{
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
		return (1);
	}
	else
		path = ft_strdup(
			parser->args[ft_str_tab_len(parser->args) - 1]);
	pipes->saved_std = dup(STDIN_FILENO);
	pipes->redir_fd = open(path, O_RDONLY, S_IRWXU);
	dup2(pipes->redir_fd, STDIN_FILENO);
	pipes->redir_eta = 2;
	clean_args(parser);
	free(path);
	return (0);
}

int		redirection(t_parser *parser, t_pipes *pipes)
{
	int			i;

	i = 0;
	while (i < ft_str_tab_len(parser->args))
	{
		if (ft_strcmp(">", parser->args[i]) == 0)
			redirect_stdout(parser, pipes, i);
		else if (ft_strcmp("<", parser->args[i]) == 0)
			if (redirect_stdin(parser, pipes) != 0)
				return (1);
		i++;
	}
	return (0);
}
