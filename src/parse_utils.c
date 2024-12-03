/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:06:25 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/03 18:37:27 by joamiran         ###   ########.fr       */
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

static int	ft_flush(t_command *cmd, char **split)
{
	free_split(split);
	free(cmd->cmd);
	return (1);
}

int	set_args(t_command *cmd, char *arg)
{
	char	**split;
	int		i;
	int		num_args;

	i = 0;
	num_args = 0;
	split = ft_split2(arg, ' ');
	if (!split)
		return (1);
	while (split[num_args])
		num_args++;
	cmd->args = ft_calloc(sizeof(char *), num_args + 1);
	if (!cmd->args)
		return (ft_flush(cmd, split));
	while (split[i])
	{
		cmd->args[i] = ft_strdup(split[i]);
		if (!cmd->args[i])
		{
			free_split(cmd->args);
			return (ft_flush(cmd, split));
		}
		i++;
	}
	cmd->args[i] = NULL;
	free_split(split);
	return (0);
}

int	set_comnargs(t_command *cmd, char *arg)
{
	if (!cmd || !arg)
		return (1);
	if (set_commands(cmd, arg) == 1 || set_args(cmd, arg) == 1)
		return (1);
	return (0);
}
