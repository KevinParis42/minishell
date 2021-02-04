/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:20:34 by kevin             #+#    #+#             */
/*   Updated: 2021/01/29 20:01:29 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		exec_builtin(t_parser *parser, char **mini_env[])
{
	if (ft_strcmp("exit", parser->args[0]) == 0)
		return (exit_builtin(parser));
	else if (ft_strcmp("pwd", parser->args[0]) == 0)
	{
		pwd_builtin(*mini_env);
		ft_putchar('\n');
	}
	else if (ft_strcmp("env", parser->args[0]) == 0)
		env_builtin(*mini_env);
	else if (ft_strcmp("cd", parser->args[0]) == 0)
	{
		if (cd_builtin(parser->args, mini_env) == 0)
			return (1);
	}
	else if (ft_strcmp("export", parser->args[0]) == 0)
		return (export_builtin(parser->args_spaced, mini_env));
	else if (ft_strcmp("unset", parser->args[0]) == 0)
		return (unset_builtin(parser->args[1], mini_env));
	else if (ft_strcmp("echo", parser->args[0]) == 0)
		echo_builtin(parser->args_spaced);
	return (0);
}

int		is_builtin(char *command)
{
	if (ft_strcmp("exit", command) == 0)
		return (1);
	else if (ft_strcmp("pwd", command) == 0)
		return (1);
	else if (ft_strcmp("env", command) == 0)
		return (1);
	else if (ft_strcmp("cd", command) == 0)
		return (1);
	else if (ft_strcmp("export", command) == 0)
		return (1);
	else if (ft_strcmp("unset", command) == 0)
		return (1);
	else if (ft_strcmp("echo", command) == 0)
		return (1);
	else
		return (0);
}

int		command_exist(t_parser *parser, char **mini_env[])
{
	if (parser->args[0][0] == '/' ||
		(parser->args[0][0] == '.' && parser->args[0][1] == '/'))
		parser->bin_path = ft_strdup(parser->args[0]);
	else
		parser->bin_path = find_path(parser->args[0], *mini_env);
	if (parser->bin_path == NULL && is_builtin(parser->args[0]) != 1)
	{
		ft_putstr_fd(parser->args[0], STDERR_FILENO);
		if (ft_strcmp(parser->args[0], "\n") != 0)
			ft_putendl_fd(": command not found", STDERR_FILENO);
		return (-1);
	}
	return (1);
}
