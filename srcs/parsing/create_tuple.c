/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tuple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:36:51 by user42            #+#    #+#             */
/*   Updated: 2021/02/01 00:58:34 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			special_char_tuple(int i, char *line, t_tuples **token_list)
{
	t_tuples	new_token;

	new_token.type = ft_strdup("specialChar");
	new_token.content = ft_substr(line, i, 1);
	*token_list = realloc_tuples(*token_list, new_token);
	return (++i);
}

int			var_tuple(int i, char *line, t_tuples **token_list)
{
	int			j;
	t_tuples	new_token;

	j = i + 1;
	new_token.type = ft_strdup("var");
	while (j < (int)ft_strlen(line))
	{
		if (!ft_isalnum(line[j]))
		{
			if (line[j] == '?' && line[j - 1] == '$')
			{
				j++;
				break ;
			}
			else
				break ;
		}
		j++;
	}
	new_token.content = ft_substr(line, i, j - i);
	*token_list = realloc_tuples(*token_list, new_token);
	if (line[j] == ';')
		j--;
	return (j);
}

int			command_tuple(int i, char *line, t_tuples **token_list)
{
	int			j;
	t_tuples	new_token;

	j = i;
	new_token.type = ft_strdup("command");
	if (line[j] == '-')
		j++;
	while (j < (int)ft_strlen(line))
	{
		if (line[j] == ' ' || (is_special_char(line[j]) == 1 &&
			(line[j] != '!' && line[j] != '@' && line[j] != '#' &&
			line[j] != '%' && line[j] != '-' && line[j] != '_' &&
			line[j] != '+' && line[j] != '.' && line[j] != '/')))
			break ;
		j++;
	}
	new_token.content = ft_substr(line, i, j - i);
	*token_list = realloc_tuples(*token_list, new_token);
	return (j);
}

int			path_tuple(int i, char *line, t_tuples **token_list)
{
	int			j;
	t_tuples	new_token;

	j = i;
	new_token.type = ft_strdup("path");
	while ((j < (int)ft_strlen(line)) && (ft_isalnum(line[j]) == 1 ||
				(line[j] == '.' || line[j] == '/')))
		j++;
	new_token.content = ft_substr(line, i, j - i);
	*token_list = realloc_tuples(*token_list, new_token);
	return (j);
}

int			strong_string_tuple(int i, char *line, t_tuples **token_list)
{
	int			j;
	t_tuples	new_token;

	j = ++i;
	new_token.type = ft_strdup("string");
	while (line[j] && line[j] != '\'')
	{
		if (line[j] == '\\')
			j++;
		j++;
	}
	new_token.content = ft_substr(line, i, j - i);
	*token_list = realloc_tuples(*token_list, new_token);
	return (++j);
}
