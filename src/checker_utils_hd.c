/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils_hd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:57:41 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/09 19:46:13 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int arg_check_hd (int argc)
{
    if (argc < 6)
        return (ft_printf("Error: Not enough arguments\n"));
    return (0);
}

int params_check_hd(int argc, char **argv)
{
    (void)argv;
    if (arg_check_hd(argc) != 0)
        return (1);
 //   if (file_access_check(argv[argc - 1]) != 0)
 //       return (1);
    return (0);
}

int assign_innoutfiles_hd(t_pipe *pipex, int argc, char **argv)
{
    pipex->infile = setup_heredoc(argv[2]);
    if (pipex->infile == -1)
        return (ft_printf("Error: cannot open temporary file\n"));
    pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipex->outfile == -1)
    {
        close(pipex->infile);
        return (ft_printf("Error: %s: No such file or directory\n", argv[argc - 1]));
    }
    return (0);
}

int validation_hd(int argc, char **argv, char **envp)
{
    char	*path_env;

    if (!envp || !*envp || envp[0] == NULL || envp[0][0] == '\0')
        return (ft_printf("Error: No environment\n"));
    path_env = get_env_var(envp, "PATH");
    if (!path_env || !*path_env || path_env[0] == '\0')
        return (ft_printf("Error: No PATH in environment\n"));
    if (params_check_hd(argc, argv) == 1)
        return (ft_printf("Error: Invalid parameters\n"));
    return (0);
}



