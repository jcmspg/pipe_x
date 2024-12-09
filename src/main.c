/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:27:20 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/09 19:27:21 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    if (argc < 5)
    {
        ft_printf("Error: Invalid number of arguments.\n");
        ft_printf("Usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
        ft_printf("   or: %s here_doc LIMITER cmd1 cmd2 file2\n", argv[0]);
        return (1);
    }
    if (ft_strncmp(argv[1], "here_doc", 8) == 0)
        ft_here_doc(argc, argv, envp);
    else
        ft_pipex(argc, argv, envp);
    return (0);
}
