/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   returns.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 09:31:27 by kevin             #+#    #+#             */
/*   Updated: 2021/01/29 20:03:45 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		failed_exec(int error_no)
{
	strerror(error_no);
	if (error_no == EAGAIN)
		return (126);
	return (127);
}

int		return_values(int status)
{
	if (WIFEXITED(status) == 1)
		return (WEXITSTATUS(status));
	else
		return (130);
	return (-1);
}
