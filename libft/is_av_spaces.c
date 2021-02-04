/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 13:41:42 by kparis            #+#    #+#             */
/*   Updated: 2021/01/23 02:15:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_av_spaces(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i][0] == ' ' && av[i][1] == 0)
			return (1);
		i++;
	}
	return (0);
}

int		with_no_av_spaces(char **av, int *n_option)
{
	int	i;

	i = 0;
	if (n_option)
		i++;
	while (av[i])
	{
		ft_putstr(av[i]);
		if (av[i + 1])
			ft_putchar(' ');
		i++;
	}
	return (0);
}
