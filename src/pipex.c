/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:01:27 by joamiran          #+#    #+#             */
/*   Updated: 2024/11/26 21:21:22 by joamiran         ###   ########.fr       */
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

    if (!(pipex = init_pipex(argc, argv, envp)))
        return (1);

    ft_printf("pipex successfully initialized\n");





    // create a pipe

    // fork the pipe
    
    // print the pipe structure AND ITS CONTENTS
    ft_printf("infile: %d\n", pipex->infile);
    ft_printf("outfile: %d\n", pipex->outfile);
    ft_printf("n_cmds: %d\n", pipex->n_cmds);
    for (int i = 0; i < pipex->n_cmds; i++)
    {
        ft_printf("cmd: %s\n", pipex->cmds[i]->cmd);
        ft_printf("path: %s\n", pipex->cmds[i]->path);
    }


    return (0);
}
