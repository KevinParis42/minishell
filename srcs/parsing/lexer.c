/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:52:13 by user42            #+#    #+#             */
/*   Updated: 2021/01/31 23:50:43 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			token_list_len(t_tuples *token_list)
{
	int i;

	i = 0;
	if (token_list)
	{
		while (token_list[i].last != 1)
			i++;
		return (i + 1);
	}
	return (-1);
}

void		free_token_list(t_tuples *token_list)
{
	int i;

	i = 0;
	while (i < token_list_len(token_list))
	{
		free(token_list[i].type);
		free(token_list[i].content);
		i++;
	}
	free(token_list);
}

int			malloc_tkn_list(t_tuples **new_token_list,
	t_tuples *old_token_list, int tkn_list_len)
{
	if (!old_token_list)
	{
		if (!(*new_token_list = malloc(sizeof(t_tuples))))
			return (0);
	}
	else
	{
		if (!(*new_token_list = malloc(sizeof(t_tuples) * (tkn_list_len + 1))))
			return (0);
	}
	return (1);
}

t_tuples	*realloc_tuples(t_tuples *old_token_list, t_tuples new_token)
{
	t_tuples	*new_token_list;
	int			i;
	int			tkn_list_len;

	new_token_list = 0;
	i = 0;
	tkn_list_len = token_list_len(old_token_list);
	if (malloc_tkn_list(&new_token_list, old_token_list, tkn_list_len) == 0)
		return (0);
	while (i < tkn_list_len)
	{
		new_token_list[i].type = ft_strdup(old_token_list[i].type);
		new_token_list[i].content = ft_strdup(old_token_list[i].content);
		new_token_list[i++].last = 0;
	}
	new_token_list[i].type = ft_strdup(new_token.type);
	new_token_list[i].content = ft_strdup(new_token.content);
	new_token_list[i].last = 1;
	free_token_list(old_token_list);
	free(new_token.type);
	free(new_token.content);
	return (new_token_list);
}

t_tuples	*lexer(char *line)
{
	t_tuples	*token_list;
	int			i;

	i = 0;
	token_list = NULL;
	while (i < (int)ft_strlen(line))
	{
		if (line[i] == '$')
			i = var_tuple(i, line, &token_list);
		else if (ft_isalnum(line[i]) || line[i] == '-')
			i = command_tuple(i, line, &token_list);
		else if (line[i] == '.' || line[i] == '/')
			i = path_tuple(i, line, &token_list);
		else if (line[i] == '\'' && line[i - 1] != '\\')
			i = strong_string_tuple(i, line, &token_list);
		else if (is_special_char(line[i]) == 1)
			i = special_char_tuple(i, line, &token_list);
		else
			i++;
	}
	return (token_list);
}
