/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weak_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:42:34 by user42            #+#    #+#             */
/*   Updated: 2021/01/31 16:13:38 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			skip_backslash(int i, char c, char c2)
{
	if (c == '\\')
		if (c2 == '$' || c2 == '\'' || c2 == '\"' || c2 == '\\')
			return (i + 1);
	return (i);
}

int			save_new_tuple
	(t_tuples *token_list, t_tuples **new_token_list, int i, t_tuples new_token)
{
	if (token_list[i].content[0] == '\\')
		i++;
	if (i > 0 && token_list[i - 1].content[0] == '\\')
		new_token.type = ft_strdup("string");
	else
		new_token.type = ft_strdup(token_list[i].type);
	new_token.content = ft_strdup(token_list[i].content);
	*new_token_list = realloc_tuples(*new_token_list, new_token);
	return (i);
}

int			weak_to_strong
	(t_tuples *token_list, t_tuples **new_token_list, int i, char **mini_env[])
{
	t_tuples	new_token;

	new_token.content = ft_strdup("");
	if (token_list[i].content[0] == '\"')
	{
		while (token_list[++i].content[0] != '\"')
		{
			i = skip_backslash(i, token_list[i].content[0],
				token_list[i + 1].content[0]);
			if (ft_strcmp(token_list[i].type, "var") == 0 && \
				token_list[i - 1].content[0] != '\\')
				new_token.content = ft_strjoin(new_token.content,
					get_var_value(token_list[i].content, *mini_env));
			else
				new_token.content =
					ft_strjoin(new_token.content, token_list[i].content);
		}
		new_token.type = ft_strdup("string");
		*new_token_list = realloc_tuples(*new_token_list, new_token);
		return (i);
	}
	i = save_new_tuple(token_list, new_token_list, i, new_token);
	return (i);
}

t_tuples	*string_interpreter(t_tuples *token_list, char **mini_env[])
{
	int			i;
	t_tuples	*new_token_list;

	i = 0;
	new_token_list = NULL;
	while (i < token_list_len(token_list))
	{
		i = weak_to_strong(token_list, &new_token_list, i, mini_env);
		i++;
	}
	free_token_list(token_list);
	return (new_token_list);
}
