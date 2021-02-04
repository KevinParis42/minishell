/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop_char_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 23:26:26 by kparis            #+#    #+#             */
/*   Updated: 2021/01/24 13:31:33 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		find_str_idx(char **tab, char *str)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], str, ft_strlen(str)) == 0)
			return (i);
		i += 1;
	}
	return (-1);
}

char	**ft_pop_char_tab(char **tab, char *str)
{
	char	**new_tab;
	int		i;
	int		j;
	int		found_idx;

	i = 0;
	j = 0;
	found_idx = find_str_idx(tab, str);
	if (found_idx == -1)
		return (tab);
	if (!(new_tab = malloc(sizeof(char *) * (ft_str_tab_len(tab) + 1))))
		return (0);
	while (tab[i] && i < ft_str_tab_len(tab))
	{
		if (i == found_idx)
		{
			i++;
			continue;
		}
		new_tab[j++] = ft_strdup(tab[i++]);
	}
	ft_free_str_tab(tab, ft_str_tab_len(tab));
	new_tab[j] = 0;
	return (new_tab);
}
