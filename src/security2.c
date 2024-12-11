/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:52:17 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/11 21:42:11 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_file_permissions(int argc, char **argv)
{
	int	fd1;
	int	fd2;

	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1)
		return (ft_printf_fd(2, "Error: %s: No such file or directory\n",
				argv[1]));
	close(fd1);
	fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd2 == -1)
		return (ft_printf_fd(2, "Error: %s: No such file or directory\n",
				argv[argc - 1]));
	close(fd2);
	if ((access(argv[1], F_OK) == -1) || (access(argv[argc - 1], F_OK) == -1))
		return (ft_printf_fd(2, "Error: %s: No such file or directory\n",
				argv[1]));
	if ((access(argv[1], R_OK) == -1) || (access(argv[argc - 1], W_OK) == -1))
		return (ft_printf_fd(2, "Error: %s: Permission denied\n", argv[1]));
	return (0);
}

int	check_for_out_permissions(int argc, char **argv)
{
	int	fd;

	fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_printf("Error: %s: No such file or directory\n", argv[argc - 1]);
		return (1);
	}
	close(fd);
	if (access(argv[argc - 1], F_OK) == -1)
	{
		ft_printf("Error: %s: No such file or directory\n", argv[argc - 1]);
		return (1);
	}
	if (access(argv[argc - 1], W_OK) == -1)
	{
		ft_printf("Error: %s: Permission denied\n", argv[argc - 1]);
		return (1);
	}
	return (0);
}
