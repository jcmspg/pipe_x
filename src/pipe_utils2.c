/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:51:33 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/11 20:47:19 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// dup handles
void	dup_handles(t_pipe *pipex, int cmd_index)
{
	if (cmd_index == 0)
	{
		close(pipex->cmds[cmd_index]->fd[0]);
		dup2(pipex->infile, STDIN_FILENO);
		close(pipex->infile);
		dup2(pipex->cmds[cmd_index]->fd[1], STDOUT_FILENO);
		close(pipex->cmds[cmd_index]->fd[1]);
	}
	else if (cmd_index == pipex->n_cmds - 1)
	{
		close(pipex->cmds[cmd_index - 1]->fd[1]);
		dup2(pipex->outfile, STDOUT_FILENO);
		close(pipex->outfile);
		dup2(pipex->cmds[cmd_index - 1]->fd[0], STDIN_FILENO);
		close(pipex->cmds[cmd_index - 1]->fd[0]);
	}
	else
	{
		close(pipex->cmds[cmd_index - 1]->fd[1]);
		close(pipex->cmds[cmd_index]->fd[0]);
		dup2(pipex->cmds[cmd_index - 1]->fd[0], STDIN_FILENO);
		close(pipex->cmds[cmd_index - 1]->fd[0]);
		dup2(pipex->cmds[cmd_index]->fd[1], STDOUT_FILENO);
		close(pipex->cmds[cmd_index]->fd[1]);
	}
}

// fork the process
int	process_command(t_pipe *pipex, int cmd_index)
{
	dup_handles(pipex, cmd_index);
	close_pipes(pipex);
	close(pipex->infile);
	close(pipex->outfile);
	if (pipex->cmds[cmd_index]->path == NULL)
	{
		ft_printf_fd(2, "Error: command not found: %s\n",
			pipex->cmds[cmd_index]->cmd);
		clean_house(pipex);
		return (1);
	}
	(execve(pipex->cmds[cmd_index]->path, pipex->cmds[cmd_index]->args,
			pipex->envp));
	return (0);
}

void	wait_for_children(t_pipe *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->n_cmds)
	{
		waitpid(pipex->cmds[i]->pid, &pipex->cmds[i]->status, 0);
		i++;
	}
}

void	forking(t_pipe *pipex)
{
	int	i;

	i = 0;
    if (!pipex->cmds)
    {
        ft_printf_fd(2, "Error: command not found\n");
        clean_house(pipex);
        exit(1);
    }
	while (i < pipex->n_cmds)
	{
		pipex->cmds[i]->pid = fork();
		if (pipex->cmds[i]->pid == 0)
		{
			if (process_command(pipex, i) != 0)
				exit(1);
		}
		else if (pipex->cmds[i]->pid < 0)
		{
			ft_printf_fd(2, "Error: fork failed\n");
			exit(1);
		}
		else
		{
			if (i > 0)
				close(pipex->cmds[i - 1]->fd[0]);
			if (i < pipex->n_cmds - 1)
				close(pipex->cmds[i]->fd[1]);
		}
		i++;
	}
}
