/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:18:54 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/10 20:43:31 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_info(t_pipe *pipex)
{
	int	i;
	int	j;

	i = 0;
	while (i < pipex->n_cmds)
	{
		ft_printf("\033[1;36mCommand %d:\033[0m\n", i);
		ft_printf("\033[1;32mcmd: \033[0m%s\n", pipex->cmds[i]->cmd);
		j = 0;
		while (pipex->cmds[i]->args[j])
		{
			ft_printf("\033[1;33marg %d: \033[0m%s\n", j,
				pipex->cmds[i]->args[j]);
			j++;
		}
		ft_printf("\033[1;34mpath: \033[0m%s\n", pipex->cmds[i]->path);
		ft_printf("\033[1;35mpid: \033[0m%d\n", pipex->cmds[i]->pid);
		ft_printf("\033[1;31mdone: \033[0m%d\n", pipex->cmds[i]->status);
		i++;
		ft_printf("\n\033[1;37m-----------------\033[0m\n\n");
	}
	ft_printf("\033[1;32mn_cmds: \033[0m%d\n", pipex->n_cmds);
	ft_printf("\033[1;34minfile: \033[0m%d\n", pipex->infile);
	ft_printf("\033[1;34moutfile: \033[0m%d\n", pipex->outfile);
	ft_printf("\n\033[1;37m-----------------\033[0m\n\n");
	ft_printf("\033[1;32mdone\033[0m\n");
}

void exit_error(t_pipe *pipex, char *msg)
{
    ft_printf_fd(2, "\033[1;31m%s\033[0m\n", msg);
    if (pipex)
        clean_house(pipex);
    exit(1);
}
