/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:26:22 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/08 21:26:25 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void handle_hd(char *limiter, int fd)
{
    char *line;

    if (fd < 0)
        exit_error(NULL, "Error: cannot create temporary file");
    while(1)
    {
        ft_printf("heredoc> ");
        line = get_next_line(0);
        if (!line)
            exit(1);
        if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && line[ft_strlen(limiter)] == '\n')
        {
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line));
        free(line);
    }
    close(fd);
}

int setup_heredoc(char *limiter)
{
    int fd;

    fd = open(TEMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
        exit_error(NULL, strerror(errno));
    handle_hd(limiter, fd);
    fd = open(TEMP_FILE, O_RDONLY);
    if (fd == -1)
    {
        unlink(TEMP_FILE);
        exit_error(NULL, strerror(errno));
    }
     return (fd);
}



void   ft_here_doc(int argc, char **argv, char **envp)
{
    t_pipe *pipex;

    if (argc < 6)
        exit_error(NULL, "Error: invalid number of arguments");

    pipex = piping(argc, argv, envp);
    if (!pipex)
        exit_error(NULL, "Error: piping failed");

    pipex->infile = setup_heredoc(argv[2]);
    pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipex->outfile == -1)
    {
        unlink(TEMP_FILE);
        exit_error(NULL, strerror(errno));
    }

    forking(pipex);
    wait_for_children(pipex);
    unlink(TEMP_FILE);
    clean_house(pipex);
}
