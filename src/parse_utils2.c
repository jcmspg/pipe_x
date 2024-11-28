/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:28:13 by joamiran          #+#    #+#             */
/*   Updated: 2024/11/28 21:57:52 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int init_fds(t_pipe *pipex)
{
    int i;

    i = 0;
    while (i < pipex->n_cmds - 1)
    {
        pipex->cmds[i]->fd = (t_fd *)ft_calloc(sizeof(t_fd), 1);
        if (!pipex->cmds[i]->fd)
            return (1);
        ft_printf("command %d\n", i);
        ft_printf("fd[1] = %p\n", (&pipex->cmds[i]->fd->fd[1]));
        ft_printf("fd[0] = %p\n", (&pipex->cmds[i]->fd->fd[0]));
        i++;
    }
    return (0);
}
