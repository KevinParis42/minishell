/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:09:50 by user42            #+#    #+#             */
/*   Updated: 2021/02/01 15:23:43 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		var_into_cmd(t_parser *parser,
	t_tuples *token_list, int i, int *ret)
{
	char	**splited_var;
	int		k;

	k = 0;
	if (ft_strcmp(token_list[i].content, "$?") == 0)
	{
		parser->args = ft_realloc_char_tab(parser->args,
			ft_itoa(*ret));
		parser->args_spaced = ft_realloc_char_tab(parser->args_spaced,
			ft_itoa(*ret));
	}
	else
	{
		splited_var = ft_split(
			get_var_value(token_list[i].content, g_mini_env), ' ');
		while (splited_var[k])
		{
			parser->args = ft_realloc_char_tab(parser->args, splited_var[k]);
			parser->args_spaced = ft_realloc_char_tab(
				parser->args_spaced, splited_var[k++]);
		}
	}
}

void		parse_var(t_parser *parser, t_tuples *token_list, int i, int *ret)
{
	if (ft_str_tab_len(parser->args) == 0)
		var_into_cmd(parser, token_list, i, ret);
	else
	{
		if (ft_strcmp(token_list[i].content, "$?") == 0)
		{
			parser->args = ft_realloc_char_tab(parser->args, ft_itoa(*ret));
			parser->args_spaced = ft_realloc_char_tab(parser->args_spaced,
				ft_itoa(*ret));
		}
		else
		{
			parser->args = ft_realloc_char_tab(parser->args,
				get_var_value(token_list[i].content, g_mini_env));
			parser->args_spaced = ft_realloc_char_tab(parser->args_spaced,
				get_var_value(token_list[i].content, g_mini_env));
		}
	}
}

void		args_to_exec(t_parser *parser, t_pipes *pipes, int i, int *ret)
{
	if (i < token_list_len(parser->token_list) &&
		parser->token_list[i].content[0] == '|')
		pipes->pipe_needed = 1;
	*ret = exec_single_command(parser, pipes, &g_mini_env);
	if (*ret == -1)
	{
		ft_free_str_tab(parser->args, ft_str_tab_len(parser->args));
		ft_free_str_tab(parser->args_spaced,
			ft_str_tab_len(parser->args_spaced));
		free_token_list(parser->token_list);
		ft_free_str_tab(g_mini_env, ft_str_tab_len(g_mini_env));
		exit(parser->exit_value);
	}
	parser->exit_value = *ret;
	ft_free_str_tab(parser->args, ft_str_tab_len(parser->args));
	ft_free_str_tab(parser->args_spaced, ft_str_tab_len(parser->args_spaced));
}

int			parse_cmd(t_parser *parser, int i, int *ret)
{
	while (i < token_list_len(parser->token_list) &&
		(is_delimiter(parser->token_list[i].content[0]) == 0 ||
		ft_strcmp(parser->token_list[i].type, "string") == 0))
	{
		if (parser->token_list[i].content[0] == ' ')
		{
			parser->args_spaced = ft_realloc_char_tab(parser->args_spaced,
				parser->token_list[i++].content);
			continue;
		}
		else if (ft_strcmp(parser->token_list[i].type, "var") == 0)
			parse_var(parser, parser->token_list, i, ret);
		else
		{
			parser->args = ft_realloc_char_tab(parser->args,
				parser->token_list[i].content);
			parser->args_spaced = ft_realloc_char_tab(parser->args_spaced,
				parser->token_list[i].content);
		}
		i++;
	}
	return (i);
}

int			parser(t_tuples *token_list, int *ret)
{
	int			i;
	t_pipes		pipes;
	t_parser	parser;

	i = 0;
	parser.exit_value = *ret;
	parser.token_list = token_list;
	if (check_synthax(&parser) != 0)
		return (2);
	while (i < token_list_len(token_list))
	{
		parser.args = NULL;
		parser.args_spaced = NULL;
		i = parse_cmd(&parser, i, ret);
		if (parser.args)
			args_to_exec(&parser, &pipes, i, ret);
		i++;
	}
	free_token_list(token_list);
	return (1);
}
