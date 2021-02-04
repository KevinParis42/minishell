/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:20:34 by kevin             #+#    #+#             */
/*   Updated: 2021/01/29 19:41:34 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		is_regular_file(const char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

int		is_regular_directory(const char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

int		check_synthax(t_parser *parser)
{
	int	i;
	int err;

	i = 0;
	err = 0;
	if (token_list_len(parser->token_list) == 1 &&
		is_delimiter(parser->token_list[i].content[0]) == 1)
		err = 1;
	while (i < token_list_len(parser->token_list))
	{
		if (i > 0 && (is_delimiter(parser->token_list[i].content[0]) == 1 &&
			is_delimiter(parser->token_list[i - 1].content[0]) == 1))
			err = 1;
		i++;
	}
	if (err == 1)
	{
		ft_putendl_fd("Synthax error", STDERR_FILENO);
		g_ret = 2;
		return (1);
	}
	return (0);
}
