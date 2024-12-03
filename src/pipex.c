/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:01:27 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/03 21:40:30 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe	*pipex;
	int		i;

	i = 0;
    pipex = piping(argc, argv, envp);
	print_info(pipex);
    forking(pipex);
    close_pipes(pipex);
	wait_for_children(pipex);
    clean_house(pipex);
	return (0);
}
