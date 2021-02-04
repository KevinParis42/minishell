/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:28:52 by user42            #+#    #+#             */
/*   Updated: 2021/01/29 20:18:53 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_quotes(char *line)
{
	int		count;
	int		count2;
	int		i;

	count = 0;
	count2 = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\"' && line[i - 1] != '\\')
			count++;
		if (line[i] == '\'' && line[i - 1] != '\\')
			count2++;
	}
	if (count % 2 != 0 || count2 % 2 != 0)
	{
		ft_putendl_fd("Please complete string", STDERR_FILENO);
		free(line);
		g_ret = 1;
		return (-1);
	}
	return (0);
}

void	user_line_two(char **mini_env)
{
	if (g_ret != 130 || g_old_ret == 130)
	{
		pwd_builtin(mini_env);
		ft_putstr("> ");
		g_old_ret = 0;
	}
	else
	{
		g_old_ret = 130;
	}
}

char	*get_user_line(char *mini_env[])
{
	char	*line;
	char	*line2;

	line = NULL;
	line2 = ft_strdup("");
	user_line_two(mini_env);
	while (get_next_line(0, &line) == 0)
	{
		if (line[0] != '\0')
			line2 = ft_strjoin(line2, line);
		if (ft_strcmp(line2, "") == 0)
		{
			ft_putendl("exit");
			exit(g_ret);
		}
		continue;
	}
	line = ft_strjoin(line2, line);
	if (check_quotes(line) == -1)
		return (0);
	free(line2);
	return (line);
}
