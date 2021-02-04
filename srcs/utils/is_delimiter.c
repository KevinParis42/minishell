/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_delimiter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 18:48:00 by kevin             #+#    #+#             */
/*   Updated: 2021/01/31 16:36:47 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			is_delimiter(char c)
{
	if (c == ';' || c == '|')
		return (1);
	return (0);
}

int			is_special_char(char c)
{
	if ((c >= 32 && c <= 47) || (c >= 58 && c <= 64)
	|| (c >= 91 && c <= 96) || (c >= 123 && c <= 126))
		return (1);
	return (0);
}

int			need_redirect(t_parser *parser)
{
	int		i;

	i = 0;
	while (i < ft_str_tab_len(parser->args))
	{
		if (ft_strchr(parser->args[i], '>') != NULL ||
			ft_strchr(parser->args[i], '<') != NULL)
			return (1);
		i++;
	}
	return (0);
}
