/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:26:22 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/11 17:45:27 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_here_doc(int argc, char **argv, char **envp)
{
	t_pipe	*pipex;

	pipex = piping_hd(argc, argv, envp);
	forking(pipex);
	wait_for_children(pipex);
	unlink(TEMP_FILE);
	clean_house(pipex);
}
