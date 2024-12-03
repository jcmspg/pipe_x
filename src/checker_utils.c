/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:43:40 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/03 18:36:54 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	arg_check(int argc)
{
	if (argc < 5)
		return (ft_printf("Error: Not enough arguments\n"));
	return (0);
}

int	file_access_check(char *file)
{
	if (access(file, F_OK) == -1)
		return (ft_printf("Error: %s: No such file or directory\n", file));
	return (0);
}

int	params_check(int argc, char **argv)
{
	if (arg_check(argc))
		return (1);
	if (file_access_check(argv[1]) || file_access_check(argv[argc - 1]))
		return (1);
	return (0);
}

int	assign_innoutfiles(t_pipe *pipex, int argc, char **argv)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		return (ft_printf("Error: %s: No such file or directory\n", argv[1]));
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
	{
		close(pipex->infile);
		return (ft_printf("Error: %s: No such file or directory\n", argv[argc
				- 1]));
	}
	return (0);
}

char	*ft_strjoin2(char *paths, char *cmd)
{
	char	*path1;
	char	*path2;

	path1 = ft_strjoin(paths, "/");
	path2 = ft_strjoin(path1, cmd);
	free(path1);
	return (path2);
}
