/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:01:27 by joamiran          #+#    #+#             */
/*   Updated: 2024/11/27 21:03:22 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



// create a pipe
// |         fork the pipe
// |         then i duplicate the parent process
// close the pipe
// work with the child process




int	main(int argc, char **argv, char **envp)
{
    t_pipe  *pipex;
    
    pipex = init_pipex(argc, argv, envp);
    if (!pipex)
        return (1);

    ft_printf("pipex successfully initialized\n");

    // create the pipes
    if (make_pipe(pipex) != 0)
    {
        free_pipex(pipex);
        return (1);
    }
    ft_printf("pipes successfully created\n");


    // fork the pipe
    
    // print the pipe structure AND ITS CONTENTS
    ft_printf("infile: %d\n", pipex->infile);
    ft_printf("outfile: %d\n", pipex->outfile);
   
    for (int i = 0; i < pipex->n_cmds; i++)
    {
        ft_printf("cmd: %s\n", pipex->cmds[i]->cmd);
        ft_printf("path: %s\n", pipex->cmds[i]->path);

        // print the args of the command
        ft_printf("args: ");
    
        char **args = pipex->cmds[i]->args;  // Create a temporary pointer for iteration
        if (args)
        {
            while (*args)
            {
                ft_printf("%s ", *args);  // Print each argument
                args++;  // Move to the next argument
            }
        }
        ft_printf("\n");

        ft_printf("fds: %d %d\n", pipex->cmds[i]->fd->fd[0], pipex->cmds[i]->fd->fd[1]);
    }





    // close the pipe
    
    close(pipex->infile);
    close(pipex->outfile);

    //print all the commands and their arguments



    // free everything
    free_pipex(pipex);
    
    ft_printf("pipex successfully freed\n");


    return (0);
}
