/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:49:42 by user42            #+#    #+#             */
/*   Updated: 2021/01/29 20:35:29 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		exit_builtin(t_parser *parser)
{
	ft_putendl("exit");
	if (parser->args[1])
	{
		if (ft_isdigit(parser->args[1][0]) != 1)
		{
			ft_putstr_fd(ft_strjoin("exit: ", parser->args[1]), STDERR_FILENO);
			ft_putendl_fd(" : numeric argument required", STDERR_FILENO);
		}
		else
		{
			parser->exit_value = ft_atoi(parser->args[1]);
			if (parser->exit_value > LLONG_MAX ||
				parser->exit_value <= LLONG_MIN)
				parser->exit_value = parser->exit_value % 256;
		}
	}
	return (-1);
}
