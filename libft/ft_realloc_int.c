/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:50:21 by kparis            #+#    #+#             */
/*   Updated: 2021/01/23 02:13:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_realloc_int(int *tab, int size, int nbr)
{
	int *final_tab;
	int i;

	i = 0;
	final_tab = malloc(sizeof(int) * (size + 1));
	while (i < size)
	{
		final_tab[i] = tab[i];
		i += 1;
	}
	final_tab[i] = nbr;
	if (size)
		free(tab);
	return (final_tab);
}
