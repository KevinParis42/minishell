/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:29:09 by kevin             #+#    #+#             */
/*   Updated: 2021/01/31 16:35:35 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		*dot_remover(char *path)
{
	int i;

	i = 0;
	while (path[i])
		i++;
	i = i - 2;
	while (path[i] != '/')
		i--;
	path[i] = 0;
	if (i == 0)
	{
		path[0] = '/';
		path[1] = 0;
	}
	return (path);
}

void		change_path(char *path, char *buff, char **mini_env[])
{
	(void)buff;
	chdir(path);
	if (path[1] == '/')
		path++;
	path = ft_strjoin("PWD=", path);
	edit_env_var(path, mini_env);
}

char		**cd_builtin_part_two(char **mini_env[], char **args_split)
{
	int		i;
	char	*path;
	char	buff[4096];

	i = -1;
	path = ft_strjoin(getcwd(buff, sizeof(buff)), "");
	while (args_split[++i])
	{
		if (ft_strcmp(".", args_split[i]) == 0)
		{
			if (i == 0 && !args_split[i + 1])
				return (NULL);
		}
		if (ft_strcmp("..", args_split[i]) && ft_strcmp(".", args_split[i]))
			path = ft_strjoin(path, "/");
		if (ft_strcmp("..", args_split[i]) && ft_strcmp(".", args_split[i]))
			path = ft_strjoin(path, args_split[i]);
		if (ft_strcmp("..", args_split[i]) == 0)
			path = dot_remover(path);
	}
	if (is_regular_directory(path))
		change_path(path, buff, mini_env);
	else
		display_error(path);
	return (NULL);
}

char		**cd_builtin_part(char **args, char **mini_env[])
{
	char **args_splitted;
	char *path;

	args_splitted = ft_split(args[1], '/');
	if (args[1][0] == '/')
	{
		if (is_regular_directory(args[1]))
		{
			chdir(args[1]);
			path = ft_strjoin("PWD=", args[1]);
			edit_env_var(path, mini_env);
		}
		else
			display_error(args[1]);
	}
	else
		return (cd_builtin_part_two(mini_env, args_splitted));
	return (NULL);
}

char		**cd_builtin(char **args, char **mini_env[])
{
	char	*home;

	home = get_var_value("HOME", *mini_env);
	if (ft_strcmp(home, "") == 0)
	{
		ft_putendl_fd("HOME not set", STDERR_FILENO);
		return (NULL);
	}
	if (ft_str_tab_len(args) > 2)
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		return (NULL);
	}
	if (ft_str_tab_len(args) == 1)
	{
		chdir(home);
		home = ft_strjoin("PWD=", home);
		edit_env_var(home, mini_env);
		return (NULL);
	}
	else
		return (cd_builtin_part(args, mini_env));
}
