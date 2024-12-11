/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:06:25 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/11 18:20:32 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_commands(int argc)
{
	int	n_cmds;

	n_cmds = argc - 3;
	return (n_cmds);
}

int	set_commands(t_command *cmd, char *arg)
{
	char	**split;

	split = ft_split(arg, ' ');
	if (!split)
		return (1);
	cmd->cmd = ft_strdup(split[0]);
	if (!cmd->cmd)
	{
		free_split(split);
		return (1);
	}
	free_split(split);
	return (0);
}

int	ft_flush(t_command *cmd, char **split)
{
	free_split(split);
	free(cmd->cmd);
	return (1);
}

int	set_comnargs(t_command *cmd, char *arg)
{
	if (!cmd || !arg)
		return (1);
	if (set_commands(cmd, arg) == 1 || set_args(cmd, arg) == 1)
		return (1);
	return (0);
}
