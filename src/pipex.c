/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:01:27 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/11 17:46:12 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipex(int argc, char **argv, char **envp)
{
	t_pipe	*pipex;

	pipex = piping(argc, argv, envp);
	forking(pipex);
	wait_for_children(pipex);
	clean_house(pipex);
}
