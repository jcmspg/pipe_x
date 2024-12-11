/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:52:17 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/11 20:53:27 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_file_permissions(int argc, char **argv)
{
	if (access(argv[1], F_OK) == -1)
	{
		ft_printf("Error: %s: No such file or directory\n", argv[1]);
		return (1);
	}
	if (access(argv[1], R_OK) == -1)
	{
		ft_printf("Error: %s: Permission denied\n", argv[1]);
		return (1);
	}
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
