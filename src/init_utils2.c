/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:48:04 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/11 19:07:01 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
char	*find_command(char *cmd, char **envp)
{
	char	*path;
	char	**paths;
	int		i;
	int		j;

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
*/
static char	**find_path(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			if (!paths)
				return (NULL);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

/*
static char	*get_path(char *cmd, char **envp)
{
	char	*path;
	char	**paths;
	int		i;

	i = 0;
	paths = find_path(envp);
	if (!paths)
		return (NULL);
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
	return (NULL);
}
*/

static char	*build_check(char **paths, char *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin2(paths[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

static char	*get_path(char *cmd, char **envp)
{
	char	*path;
	char	**paths;

	paths = find_path(envp);
	if (!paths)
		return (NULL);
	path = build_check(paths, cmd);
	free_split(paths);
	return (path);
}

char	*find_command(char *cmd, char **envp)
{
	char	*path;

	path = get_path(cmd, envp);
	return (path);
}
