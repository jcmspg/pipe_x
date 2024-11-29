/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:01:27 by joamiran          #+#    #+#             */
/*   Updated: 2024/11/29 19:59:54 by joamiran         ###   ########.fr       */
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
	{
		ft_printf("Error: No environment\n");
		return (1);
	}
	path_env = get_env_var(envp, "PATH");
	if (!path_env || !*path_env || path_env[0] == '\0')
	{
		ft_printf("Error: No PATH variable in environment\n");
		return (1);
	}
	if (params_check(argc, argv) == 1)
	{
		ft_printf("Error: Invalid parameters\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	*pipex;
    int i;
    int prev_fd;

    prev_fd = -1;

	if (validation(argc, argv, envp) == 1)
		return (1);

	pipex = init_pipex(argc, argv, envp);
	if (!pipex)
		return (1);
	
    print_info(pipex);
    
    i = 0;
    while (i < pipex->n_cmds)
    {
        if (make_pipe(pipex, i) != 0)
        {
            free_pipex(pipex);
            return (1);
        }
        if (process_command(pipex, i, prev_fd) != 0)
        {
            free_pipex(pipex);
            return (1);
        }
        if (i > 0)
            close(prev_fd);
        prev_fd = pipex->fd[0];
        i++;
    }
    
  //  wait_for_children(pipex);

	close(pipex->infile);
	close(pipex->outfile);
	free_pipex(pipex);
	return (0);
}
