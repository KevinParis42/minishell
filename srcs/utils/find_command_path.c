/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 02:21:47 by user42            #+#    #+#             */
/*   Updated: 2021/01/23 02:22:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_command(char *command, char *path)
{
	struct dirent	*dir;
	DIR				*d;

	d = opendir(path);
	if (d == NULL)
		return (NULL);
	while ((dir = readdir(d)) != NULL)
	{
		if (ft_strcmp(dir->d_name, command) == 0)
		{
			return (ft_strjoin(ft_strjoin(path, "/"), command));
			closedir(d);
		}
	}
	closedir(d);
	return (NULL);
}

char	*find_path(char *command, char **mini_env)
{
	char	**paths;
	int		i;
	char	*path;

	paths = parse_path("$PATH", mini_env);
	i = 0;
	while (paths[i])
	{
		path = find_command(command, paths[i]);
		if (path)
			return (path);
		i++;
	}
	return (NULL);
}
