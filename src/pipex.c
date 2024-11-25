/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:01:27 by joamiran          #+#    #+#             */
/*   Updated: 2024/11/25 21:07:55 by joamiran         ###   ########.fr       */
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
    int infile;
    int outfile;


    if (argc < 4)
    {
        return(ft_printf("Error: Not enough arguments\n"));
        return (1);
    }

    // split the arguments 1st is infile, 2nd is command1, then pipes, then command2, then pipes, then command3, ... , then outfile
    
    // check if the infile exists
    if (access(argv[1], F_OK) == -1)
    {
        return(ft_printf("Error: %s: No such file or directory\n", argv[1]));
        return (1);
    }
    
    // check if the outfile exists
    if (access(argv[argc - 1], F_OK) == 0)
    {
        ft_printf("Error: %s: File exists\n", argv[argc - 1]);
        return (1);
    }

    // set argv[0] and argv[argc - 1] to the infile and outfile
    infile = open(argv[1], O_RDONLY);
    
    if (infile == -1)
    {
        ft_printf("Error: %s: No such file or directory\n", argv[1]);
        return (1);
    }

    outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (outfile == -1)
    {
        ft_printf("Error: %s: No such file or directory\n", argv[argc - 1]);
        return (1);
    }

    // check for how many commands are there and how many pipes
    

    // open the infile and outfile
    // create a pipe
    // fork the pipe




    return (0);
}
