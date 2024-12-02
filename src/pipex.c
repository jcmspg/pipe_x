/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:01:27 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/02 21:00:10 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_env_var(char **envp, const char *name)
{
	int		i;
	size_t	name_len;

	name_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0
			&& envp[i][name_len] == '=')
			return (envp[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

static int	validation(int argc, char **argv, char **envp)
{
	char	*path_env;

	if (!envp || !*envp || envp[0] == NULL || envp[0][0] == '\0')
		return (ft_printf("Error: No environment\n"));
	path_env = get_env_var(envp, "PATH");
	if (!path_env || !*path_env || path_env[0] == '\0')
		return (ft_printf("Error: No PATH in environment\n"));
	if (params_check(argc, argv) == 1)
		return (ft_printf("Error: Invalid parameters\n"));
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	*pipex;
    int    i;
    
    i = 0;
	if (validation(argc, argv, envp) == 1)
		return (1);
	pipex = init_pipex(argc, argv, envp);
	if (!pipex)
		return (1);
	if (make_pipe(pipex) != 0)
	{
		free_pipex(pipex);
		return (ft_printf("Error: pipe failed\n"));
	}

    while (i < pipex->n_cmds)
    {
        pipex->cmds[i]->pid = fork();
        if (pipex->cmds[i]->pid == 0)
            process_command(pipex, i);
        else if (pipex->cmds[i]->pid > 0)
        {
            close_correct_pipe(pipex, i);
            waitpid(pipex->cmds[i]->pid, &pipex->cmds[i]->status, 0);
        }
        i++;
    }

//	pipex->cmds[0]->pid = fork();
//	if (pipex->cmds[0]->pid == 0)
//		process_command(pipex, 0);
//	else if (pipex->cmds[0]->pid > 0)
//	{
//		close(pipex->fd[1]);
//		waitpid(pipex->cmds[0]->pid, &pipex->cmds[0]->status, 0);
//	}
//	pipex->cmds[1]->pid = fork();
//	if (pipex->cmds[1]->pid == 0)
//	{
//		process_command(pipex, 1);
//	}
//	else if (pipex->cmds[1]->pid > 0)
//	{
//		close(pipex->fd[0]);
//		waitpid(pipex->cmds[1]->pid, &pipex->cmds[1]->status, 0);
//	}
	clean_house(pipex);
    return (0);
}
