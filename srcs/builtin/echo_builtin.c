/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 02:24:35 by user42            #+#    #+#             */
/*   Updated: 2021/01/29 15:13:31 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_echo_first_arg(char **av, int *n_option, int av_space)
{
	int		i;
	int		j;

	i = 1;
	if (!av_space)
	{
		i = with_no_av_spaces(av, n_option);
	}
	else
	{
		if (av[1] && !(ft_strncmp("-n", av[1], 0)))
			*n_option = i++;
		while (av[i] && av[i][0] && av[i][0] == '-'
			&& av[i][1] && av[i][1] == 'n')
		{
			j = 2;
			while (av[i][j] && av[i][j] == 'n')
				j++;
			if (av[i][j])
				return (i);
			i++;
		}
	}
	return (i);
}

void	ft_echo_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	echo_print(char **av, int i, int echo_first_arg)
{
	int j;

	j = echo_first_arg;
	while (j < i)
	{
		ft_echo_putstr(av[j]);
		if (av[j][0] == ' ' && !av[j][1])
			j++;
		else
		{
			if ((j != (i - 1)))
				ft_putchar(' ');
			j++;
		}
	}
}

int		is_n(char *str)
{
	if (ft_strcmp(str, "-n") == 0)
		return (1);
	else
		return (0);
}

int		echo_builtin(char **av)
{
	int		i;
	int		echo_first_arg;
	int		n_option;
	int		av_space;

	av_space = is_av_spaces(av);
	n_option = 0;
	echo_first_arg = ft_echo_first_arg(av, &n_option, av_space);
	i = echo_first_arg;
	while (av[i])
		i++;
	if (av_space == 1)
		echo_print(av, i, echo_first_arg);
	if (av[2])
	{
		if (is_n(av[2]) == 0)
			ft_putchar('\n');
	}
	else
		ft_putchar('\n');
	return (0);
}
