/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exist_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:55:06 by user42            #+#    #+#             */
/*   Updated: 2021/01/21 20:06:38 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exist_path(char *path)
{
	DIR		*rep;
	char	*cut_path;

	rep = opendir(path);
	if (rep == NULL)
	{
		cut_path = ft_cutend(path, '/');
		if (cut_path == NULL)
			return (0);
		rep = opendir(cut_path);
		if (rep == NULL)
			return (2);
	}
	return (1);
}
