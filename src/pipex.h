/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:09:34 by joamiran          #+#    #+#             */
/*   Updated: 2024/11/22 17:00:43 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../inc/lib_ft/libft.h"

typedef struct fd_pipex
{
    int fd[2];
    
    int *fd_in;
    int *fd_out;

}   t_fd;

typedef struct pipex
{
    char    **cmd;
    char    **env;
    int     *fd;
    int     *pid;
    int     *status;
    int     *i;
    int     *n;
}   t_pipex;



#endif
