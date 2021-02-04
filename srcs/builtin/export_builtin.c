/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:15:34 by user42            #+#    #+#             */
/*   Updated: 2021/01/28 22:39:11 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_export(int i, char **args)
{
	if (ft_strcmp(args[i - 1], " ") == 0)
	{
		ft_putstr_fd(ft_strjoin("export : ",
			ft_strjoin("=", args[i + 1])), STDERR_FILENO);
		ft_putendl_fd(" : not a valid identifier", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

int		check_value(char *var_name, char *value)
{
	if (ft_isalpha(var_name[0]) != 1)
	{
		ft_putstr_fd(ft_strjoin(var_name,
			ft_strjoin("=", value)), STDERR_FILENO);
		ft_putendl_fd(" : not a valid identifier", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

void	save_new_var(char *var_name, char *var_value, char **mini_env[])
{
	char	*env_entry;

	env_entry = ft_strjoin(var_name, ft_strjoin("=", var_value));
	if (ft_strcmp(get_var_value(var_name, *mini_env), ""))
		edit_env_var(env_entry, mini_env);
	else
		*mini_env = ft_realloc_char_tab(*mini_env, env_entry);
	free(var_name);
	free(var_value);
	free(env_entry);
}

int		export_builtin(char **args, char **mini_env[])
{
	char	*var_value;
	char	*var_name;
	int		i;

	i = 0;
	while (i < ft_str_tab_len(args))
	{
		if (ft_strchr(args[i], '=') == 0)
		{
			i++;
			continue;
		}
		if (check_export(i, args) == -1)
			return (1);
		var_value = ft_strdup("");
		var_name = ft_strdup(args[i - 1]);
		i++;
		if (check_value(var_name, args[i]) == -1)
			return (1);
		while (i < ft_str_tab_len(args) && ft_strncmp(args[i], " ", 2) != 0)
			var_value = ft_strjoin(var_value, args[i++]);
		save_new_var(var_name, var_value, mini_env);
		i++;
	}
	return (0);
}
