/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:13:57 by kparis            #+#    #+#             */
/*   Updated: 2021/01/29 20:35:13 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	indent_shlvl(char **mini_env[])
{
	int		shlvl;
	char	*shlvl_str;

	shlvl = ft_atoi(get_var_value("$SHLVL", *mini_env));
	shlvl++;
	shlvl_str = ft_strjoin("SHLVL=", ft_itoa(shlvl));
	edit_env_var(shlvl_str, mini_env);
	free(shlvl_str);
}

char	**create_from_empty(char **mini_env)
{
	char	buff[4096];

	mini_env = NULL;
	mini_env = ft_realloc_char_tab(mini_env,
		ft_strdup(getcwd(buff, sizeof(buff))));
	mini_env = ft_realloc_char_tab(mini_env, "LS_COLORS=");
	mini_env = ft_realloc_char_tab(mini_env,
		"LESSCLOSE=/usr/bin/lesspipe %s %s");
	mini_env = ft_realloc_char_tab(mini_env,
		"LESSOPEN=| /usr/bin/lesspipe %s");
	mini_env = ft_realloc_char_tab(mini_env, "SHLVL=0");
	mini_env = ft_realloc_char_tab(mini_env, "_=/usr/bin/env");
	return (mini_env);
}

char	**cpy_env(char **env)
{
	char	**mini_env;
	int		i;

	i = 0;
	mini_env = NULL;
	if (env == NULL || env[0] == NULL)
		return (create_from_empty(mini_env));
	if (!(mini_env = malloc(sizeof(char *) * (ft_str_tab_len(env) + 1))))
		return (0);
	while (i < ft_str_tab_len(env))
	{
		mini_env[i] = ft_strdup(env[i]);
		i++;
	}
	mini_env[i] = 0;
	return (mini_env);
}

char	*get_var_value(char *name, char *mini_env[])
{
	int		i;
	int		start;
	char	**env_var;
	char	*var_value;

	i = 0;
	start = 0;
	if (name[start] == '$')
		start++;
	while (mini_env[i])
	{
		env_var = ft_split(mini_env[i], '=');
		if (ft_strcmp(&name[start], env_var[0]) == 0)
		{
			if (env_var[1] == 0)
				var_value = ft_strdup(" ");
			else
				var_value = ft_strdup(env_var[1]);
			ft_free_str_tab(env_var, ft_str_tab_len(env_var));
			return (var_value);
		}
		i++;
	}
	ft_free_str_tab(env_var, ft_str_tab_len(env_var));
	return ("");
}

void	edit_env_var(char *var, char **mini_env[])
{
	int		i;
	char	**splited_var;
	char	**new_env;

	i = 0;
	splited_var = ft_split(var, '=');
	new_env = cpy_env(*mini_env);
	while (new_env[i])
	{
		if (ft_strncmp(splited_var[0], new_env[i],
			ft_strlen(splited_var[0])) == 0)
		{
			free(new_env[i]);
			new_env[i] = ft_strdup(var);
			break ;
		}
		i += 1;
	}
	ft_free_str_tab(splited_var, ft_str_tab_len(splited_var));
	ft_free_str_tab(*mini_env, ft_str_tab_len(*mini_env));
	*mini_env = new_env;
}
