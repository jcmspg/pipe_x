/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:54:10 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/11 17:46:30 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env_var(char **envp, const char *name)
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

t_pipe	*piping(int argc, char **argv, char **envp)
{
	t_pipe	*pipex;

	if (validation(argc, argv, envp) == 1)
		return (NULL);
	pipex = init_pipex(argc, argv, envp);
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
