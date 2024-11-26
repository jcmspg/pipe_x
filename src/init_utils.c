/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:03:47 by joamiran          #+#    #+#             */
/*   Updated: 2024/11/26 21:20:50 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *find_command(char *cmd, char **envp)
{
    char *path;
    char **paths;
    int i;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
        {
            paths = ft_split(envp[i] + 5, ':');
            if (!paths)
                return (NULL);
            i = 0;
            while (paths[i])
            {
                path = ft_strjoin(paths[i], "/");
                path = ft_strjoin(path, cmd);
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
        i++;
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
    return (cmd);
}


void assign_commands(t_pipe *pipex, char **argv)
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
            return ;
        pipex->cmds[i]->cmd = ft_strdup(argv[i + 2]);
        if (!pipex->cmds[i]->cmd)
            return ;
        path = find_command(pipex->cmds[i]->cmd, pipex->envp);
        pipex->cmds[i]->path = path;
        pipex->cmds[i]->args = NULL;
        pipex->cmds[i]->pid = NULL;
        pipex->cmds[i]->done = false;
        i++;
    }
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
    assign_commands(pipex, argv);
    return (pipex);
}


