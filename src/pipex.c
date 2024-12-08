/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:01:27 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/05 19:21:14 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe	*pipex;

	pipex = piping(argc, argv, envp);
//	while (i < pipex->n_cmds)
//	{
//		pipex->cmds[i]->pid = fork();
//		if (pipex->cmds[i]->pid == -1)
//			return (ft_printf("Error: fork failed\n"));
//		if (pipex->cmds[i]->pid == 0)
//			process_command(pipex, i);
//		i++;
//	}
    forking(pipex);
	wait_for_children(pipex);
	clean_house(pipex);
	return (0);
}
