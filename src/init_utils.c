/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:03:47 by joamiran          #+#    #+#             */
/*   Updated: 2024/11/27 20:22:36 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *find_command(char *cmd, char **envp)
{
    char *path;
    char **paths;
    int i;
    int j;

    j = 0;
    while (envp[j])
    {
        if (ft_strncmp(envp[j], "PATH=", 5) == 0)
        {
            paths = ft_split(envp[j] + 5, ':');
            if (!paths)
                return (NULL);
            i = 0;
            while (paths[i])
            {
                path = ft_strjoin2(paths[i], cmd); 
                if (!path)
                {
                    free_split(paths);
                    return (NULL);
                }
                if (access(path, F_OK) == 0)
                {
                    free_split(paths);
                    return (path);
                }
                free(path);
                i++;
            }
            free_split(paths);
        }
        j++;
    }
    return (NULL);
}

t_command *new_command(void)
{
    t_command *cmd;

    cmd = ft_calloc(sizeof(t_command), 1);
    if (!cmd)
        return (NULL);
    cmd->fd = ft_calloc(sizeof(t_fd), 1);
    if (!cmd->fd)
    {
        free(cmd);
        return (NULL);
    }
    cmd->args = NULL;
    cmd->pid = NULL;
    cmd->done = false;
    return (cmd);
}


int assign_commands(t_pipe *pipex, char **argv)
{
    int i;
    int j;
    char *path;

    i = 0;
    j = 0;
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
        pipex->cmds[i]->args = NULL;
        pipex->cmds[i]->pid = NULL;
        pipex->cmds[i]->done = false;
        i++;
    }
    return (0);
}

t_pipe *init_pipex(int argc, char **argv, char **envp)
{
    t_pipe  *pipex;

    pipex = ft_calloc(sizeof(t_pipe), 1);
    if (!pipex)
        return (NULL);
    if (params_check(argc, argv))
    {
        free(pipex);
        return (NULL);
    }
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


