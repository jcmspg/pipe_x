/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:59:10 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/09 19:14:14 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int assign_commands_hd(t_pipe *pipex, char **argv)
{
    int i;
    char *path;

    i = 0;
    while (i < pipex->n_cmds)
    {
        pipex->cmds[i] = new_command();
        if (!pipex->cmds[i])
            return (1);
        set_comnargs(pipex->cmds[i], argv[i + 3]);
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

t_pipe *init_pipex_hd(int argc, char **argv, char **envp)
{
    t_pipe *pipex;

    pipex = ft_calloc(sizeof(t_pipe), 1);
    if (!pipex)
        return (NULL);
    if (assign_innoutfiles_hd(pipex, argc, argv) != 0)
    {
        free(pipex);
        return (NULL);
    }
    pipex->n_cmds = argc - 4;
    pipex->envp = envp;
    pipex->cmds = ft_calloc(sizeof(t_command *), pipex->n_cmds);
    if (!pipex->cmds)
    {
        free_pipex(pipex);
        return (NULL);
    }
    if (assign_commands_hd(pipex, argv) != 0)
    {
        free_pipex(pipex);
        return (NULL);
    }
    return (pipex);
}

t_pipe *piping_hd(int argc, char **argv, char **envp)
{
    t_pipe *pipex;

    if (validation_hd(argc, argv, envp) == 1)
        return (NULL);
    pipex = init_pipex_hd(argc, argv, envp);
    if (!pipex)
        return (NULL);
    if (make_pipes(pipex) != 0)
    {
        free_pipex(pipex);
        ft_printf("Error: pipe failed\n");
        return (NULL);
    }
    return (pipex);
}
