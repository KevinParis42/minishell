/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:13:57 by kparis            #+#    #+#             */
/*   Updated: 2021/01/30 02:22:23 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_c_handler(int sig_num)
{
	(void)sig_num;
	ft_putchar('\n');
	pwd_builtin(g_mini_env);
	ft_putstr("> ");
	g_ret = 130;
}

void	sigquit_bs_handler(int sig_num)
{
	(void)sig_num;
	ft_putchar('\n');
	pwd_builtin(g_mini_env);
	ft_putstr("> ");
	g_ret = 131;
}

void	main_two(void)
{
	ft_putstr_fd("Too many arguments please run minishell", STDERR_FILENO);
	ft_putstr_fd(" like that : ./minishell\n", STDERR_FILENO);
}

void	main_three(void)
{
	signal(SIGINT, sigint_c_handler);
	signal(SIGQUIT, sigquit_bs_handler);
	g_old_ret = 0;
}

int		main(int ac, char **av, char *env[])
{
	char		*line;
	int			sig;
	t_tuples	*token_list;

	(void)av;
	sig = 0;
	g_ret = 0;
	g_mini_env = cpy_env(env);
	indent_shlvl(&g_mini_env);
	if (ac > 1)
		main_two();
	if (ac > 1)
		return (0);
	main_three();
	while (1)
	{
		line = NULL;
		if ((line = get_user_line(g_mini_env)) == 0)
			continue;
		token_list = lexer(line);
		free(line);
		if (parser(string_interpreter(token_list, &g_mini_env), &g_ret) == 0)
			return (0);
	}
	return (1);
}
