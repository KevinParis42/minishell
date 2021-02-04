/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:18:27 by user42            #+#    #+#             */
/*   Updated: 2021/01/28 17:48:34 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		unset_builtin(char *env_remove, char **mini_env[])
{
	if (ft_isalpha(env_remove[0]) != 1)
	{
		ft_putstr_fd(env_remove, STDERR_FILENO);
		ft_putendl_fd(" : not a valid identifier", STDERR_FILENO);
		return (1);
	}
	*mini_env = ft_pop_char_tab(*mini_env, env_remove);
	return (0);
}
