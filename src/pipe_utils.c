/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:35:56 by joamiran          #+#    #+#             */
/*   Updated: 2024/11/28 21:35:06 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	make_pipe(t_pipe *pipex, int i)
{
	if (i < 0 || i >= pipex->n_cmds - 1)
	{
		ft_printf("Error: Pipe failed\n");
		return (1);
	}
	if (pipe(pipex->cmds[i]->fd->fd) == -1)
	{
		ft_printf("Error: Pipe failed\n");
		return (1);
	}
//	pipex->cmds[i]->pid = fork();
//	if (pipex->cmds[i]->pid == -1)
//	{
//		ft_printf("Error: Fork failed\n");
//		return (1);
//	}
//	if (pipex->cmds[i]->pid == 0)
//	{
//		if (i > 0)
//			dup2(pipex->fd[i - 1].fd[0], STDIN_FILENO);
//		if (i < pipex->n_cmds - 1)
//			dup2(pipex->fd[i].fd[1], STDOUT_FILENO);
//		for (int j = 0; j < pipex->n_cmds - 1; j++)
//		{
//			close(pipex->fd[j].fd[0]);
//			close(pipex->fd[j].fd[1]);
//		}
//		execve(pipex->cmds[i]->path, pipex->cmds[i]->args, pipex->envp);
//		ft_printf("Error: Execve failed\n");
//		return (1);
//	}
//	else
//	{
//		close(pipex->fd[i].fd[1]);
//		if (i > 0)
//			close(pipex->fd[i - 1].fd[0]);
//	}
	return (0);
}
