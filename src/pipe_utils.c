/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:35:56 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/03 21:28:24 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// make ALL pipes
int	make_pipes(t_pipe *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->n_cmds - 1)
	{
		if (pipe(pipex->cmds[i]->fd) == -1)
			return (ft_printf("Error: pipe failed\n"));
		i++;
	}
	return (0);
}

// close ONE pipe
void	close_pipe(t_pipe *pipex, int cmd_index)
{
	close(pipex->cmds[cmd_index]->fd[0]);
	close(pipex->cmds[cmd_index]->fd[1]);
}

// close ALL pipes
void	close_pipes(t_pipe *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->n_cmds - 1)
	{
		close_pipe(pipex, i);
		i++;
	}
}

// close the correct pipe
void	close_correct_pipe(t_pipe *pipex, int cmd_index)
{
	if (cmd_index == 0)
		close(pipex->cmds[cmd_index]->fd[1]);
	else if (cmd_index == pipex->n_cmds - 1)
		close(pipex->cmds[cmd_index - 1]->fd[0]);
	else
		close_pipe(pipex, cmd_index);
}
