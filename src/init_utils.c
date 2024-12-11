/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:03:47 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/11 17:48:28 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = ft_calloc(sizeof(t_command), 1);
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->status = -1;
	cmd->path = NULL;
	return (cmd);
}

int	assign_commands(t_pipe *pipex, char **argv)
{
	int		i;
	char	*path;

	i = 0;
	while (i < pipex->n_cmds)
	{
		pipex->cmds[i] = new_command();
		if (!pipex->cmds[i])
			return (1);
		set_comnargs(pipex->cmds[i], argv[i + 2]);
		if (!pipex->cmds[i]->cmd)
			return (1);
		path = find_command(pipex->cmds[i]->cmd, pipex->envp);
		pipex->cmds[i]->path = path;
		pipex->cmds[i]->status = -1;
		pipex->cmds[i]->cmd_nr = i;
		i++;
	}
	return (0);
}

t_pipe	*init_pipex(int argc, char **argv, char **envp)
{
	t_pipe	*pipex;

	pipex = ft_calloc(sizeof(t_pipe), 1);
	if (!pipex)
		return (NULL);
	if (assign_innoutfiles(pipex, argc, argv))
	{
		free(pipex);
		return (NULL);
	}
	pipex->n_cmds = count_commands(argc);
	pipex->envp = envp;
	pipex->cmds = ft_calloc(sizeof(t_command *), pipex->n_cmds);
	if (!pipex->cmds)
	{
		free(pipex);
		return (NULL);
	}
	if (assign_commands(pipex, argv))
	{
		free(pipex);
		return (NULL);
	}
	return (pipex);
}
