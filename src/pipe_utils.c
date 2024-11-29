/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:35:56 by joamiran          #+#    #+#             */
/*   Updated: 2024/11/29 20:02:03 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// make pipe
int	make_pipe(t_pipe *pipex, int i)
{
    if (i < pipex->n_cmds - 1)
    {
        if (pipe(pipex->fd) == -1)
        {
            ft_printf("Error: pipe failed\n");
            return (1);
        }
    }
    return (0);
}

// fork the process
int	process_command(t_pipe *pipex, int i, int prev_fd)
{
	pipex->cmds[i]->pid = fork();
	if (pipex->cmds[i]->pid == -1)
	{
		ft_printf("Error: fork failed\n");
		return (1);
	}
	if (pipex->cmds[i]->pid == 0)
	{
		if (i == 0)
			dup2(pipex->infile, STDIN_FILENO);
		else
			dup2(prev_fd, STDIN_FILENO);
		if (i == pipex->n_cmds - 1)
			dup2(pipex->outfile, STDOUT_FILENO);
		else
			dup2(pipex->fd[1], STDOUT_FILENO);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		if (pipex->cmds[i]->path != NULL)
			execve(pipex->cmds[i]->path, pipex->cmds[i]->args, pipex->envp);
	}
	return (0);
}

// wait for the child process to finish
void	wait_for_children(t_pipe *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->n_cmds)
	{
		waitpid(pipex->cmds[i]->pid, NULL, 0);
		i++;
	}
}

// close the pipe
void	close_pipe(t_pipe *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}
