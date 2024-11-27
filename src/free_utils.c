/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:38:10 by joamiran          #+#    #+#             */
/*   Updated: 2024/11/27 19:45:26 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void free_split(char **split)
{
    int	i;

    i = 0;

    if (!split)
        return ;
    if (split[i])
    {
        while (split[i])
        {
            free(split[i]);
            i++;
        }
    }
    free(split);
}

void free_commands(t_pipe *pipex)
{
    int i;

    i = pipex->n_cmds;

    while (i--)
    {
        free(pipex->cmds[i]->cmd);
        free_split(pipex->cmds[i]->args);
        free(pipex->cmds[i]->path);
        free(pipex->cmds[i]->fd);
        free(pipex->cmds[i]);
    }
    free(pipex->cmds);
}


void free_pipex(t_pipe *pipex)
{
    free_commands(pipex);
    free(pipex);
}
