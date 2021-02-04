/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_char_tab.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 23:26:26 by kparis            #+#    #+#             */
/*   Updated: 2021/01/23 02:13:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc_char_tab(char **tab, char *str)
{
	char	**new_tab;
	int		i;

	i = 0;
	new_tab = NULL;
	if (!(new_tab = malloc(sizeof(char *) * (ft_str_tab_len(tab) + 2))))
		return (0);
	while (i < ft_str_tab_len(tab))
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	ft_free_str_tab(tab, ft_str_tab_len(tab));
	new_tab[i] = ft_strdup(str);
	i++;
	new_tab[i] = 0;
	return (new_tab);
}
