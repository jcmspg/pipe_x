/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:51:33 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/03 21:41:45 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// dup handles
void	dup_handles(t_pipe *pipex, int cmd_index)
{
	if (cmd_index == 0)
	{
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipex->cmds[cmd_index]->fd[1], STDOUT_FILENO);
	}
	else if (cmd_index == pipex->n_cmds - 1)
	{
		dup2(pipex->outfile, STDOUT_FILENO);
		dup2(pipex->cmds[cmd_index]->fd[0], STDIN_FILENO);
	}
	else
	{
		dup2(pipex->cmds[cmd_index - 1]->fd[0], STDIN_FILENO);
		dup2(pipex->cmds[cmd_index]->fd[1], STDOUT_FILENO);
	}
}

// fork the process
int	process_command(t_pipe *pipex, int cmd_index)
{
	dup_handles(pipex, cmd_index);
	close_pipe(pipex, cmd_index);
	close(pipex->infile);
	close(pipex->outfile);
	if (!pipex->cmds[cmd_index]->path)
		return (ft_printf("Error: command not found\n"));
	if (execve(pipex->cmds[cmd_index]->path, pipex->cmds[cmd_index]->args,
			pipex->envp) == -1)
		return (ft_printf("Error: execve failed\n"));
	return (0);
}

void	wait_for_children(t_pipe *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->n_cmds)
	{
		//    ft_printf("\033[0;31mWAITINGPID\033[0m\n");
		waitpid(pipex->cmds[i]->pid, &pipex->cmds[i]->status, 0);
		//    ft_printf("\033[0;31mWAITEDPID\033[0m\n");
		i++;
	}
}

void	forking(t_pipe *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->n_cmds)
	{
		pipex->cmds[i]->pid = fork();
		if (pipex->cmds[i]->pid == 0)
			process_command(pipex, i);
	//	else if (pipex->cmds[i]->pid > 0)
	//		close_correct_pipe(pipex, i);
		else
			ft_printf("Error: fork failed\n");
		i++;
	}
}
