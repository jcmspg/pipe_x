/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:01:27 by joamiran          #+#    #+#             */
/*   Updated: 2024/11/22 21:40:46 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int in;
	int out;
	int fd[2];

    pipe(fd);

    if (pipe(fd) == -1)
    {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) 
    {
        close (fd[0]);
        // do something in fd[1]
        close (fd[1]);
    }
    else
    {
        close (fd[1]);
        // do something from fd[0]
        close (fd[0]);
    }

    return (0);
}

