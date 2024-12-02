/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:35:56 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/02 20:59:14 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// make pipe
int	make_pipe(t_pipe *pipex)
{
	if (pipex->n_cmds > 1)
	{
		if (pipe(pipex->fd) == -1)
			return (ft_printf("Error: pipe failed\n"));
	}
	return (0);
}

// close the pipe
void	close_pipe(t_pipe *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

// fork the process
int	process_command(t_pipe *pipex, int cmd_index)
{
	if (cmd_index == 0)
	{
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipex->fd[1], STDOUT_FILENO);
	}
	else if (cmd_index == pipex->n_cmds - 1)
	{
		dup2(pipex->outfile, STDOUT_FILENO);
		dup2(pipex->fd[0], STDIN_FILENO);
	}
	else
	{
		dup2(pipex->fd[0], STDIN_FILENO);
		dup2(pipex->fd[1], STDOUT_FILENO);
	}
	close_pipe(pipex);
	close(pipex->infile);
	close(pipex->outfile);
	if (!pipex->cmds[cmd_index]->path)
		return (ft_printf("Error: command not found\n"));
	if (execve(pipex->cmds[cmd_index]->path, pipex->cmds[cmd_index]->args,
			pipex->envp) == -1)
		return (ft_printf("Error: execve failed\n"));
	return (0);
}

void close_correct_pipe(t_pipe *pipex, int cmd_index)
{
    if (cmd_index == 0)
        close(pipex->fd[1]);
    else if (cmd_index == pipex->n_cmds - 1)
        close(pipex->fd[0]);
    else
    {
        close(pipex->fd[0]);
        close(pipex->fd[1]);
    }
}

void clean_house(t_pipe *pipex)
{
    close_pipe(pipex);
    close(pipex->infile);
    close(pipex->outfile);
    free_pipex(pipex);
}
