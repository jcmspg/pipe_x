/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:35:56 by joamiran          #+#    #+#             */
/*   Updated: 2024/11/27 20:45:52 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	make_pipe(t_pipe *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->n_cmds)
	{
		if (pipe(pipex->cmds[i]->fd->fd) == -1)
			return (1);
        ft_printf("pipe for command %s created\n", pipex->cmds[i]->cmd);
		i++;
	}
	return (0);
}
