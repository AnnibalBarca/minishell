/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_closer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:39:15 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/24 15:33:55 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	safe_close(int *fd)
{
	if (*fd > 2)
	{
		close(*fd);
		*fd = -1;
	}
}

void	dup_and_close(int *fd, int std)
{
	if (std == STDIN_FILENO)
	{
		dup2(*fd, STDIN_FILENO);
		safe_close(fd);
	}
	if (std == STDOUT_FILENO)
	{
		dup2(*fd, STDOUT_FILENO);
		safe_close(fd);
	}
}
