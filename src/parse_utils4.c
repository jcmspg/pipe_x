/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:20:04 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/11 18:26:36 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
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
*/
int	count_args(char **split)
{
	int	i;

	if (!split)
		return (0);
	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	alloc_args(t_command *cmd, int num_args, char **split)
{
	cmd->args = ft_calloc(sizeof(char *), num_args + 1);
	if (!cmd->args)
		return (ft_flush(cmd, split));
	return (0);
}

int	copy_args(t_command *cmd, char **split)
{
	int	i;

	i = 0;
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

int	set_args(t_command *cmd, char *arg)
{
	char	**split;
	int		num_args;

	split = ft_split2(arg, ' ');
	if (!split)
		return (1);
	num_args = count_args(split);
	if (num_args == 0)
		return (ft_flush(cmd, split));
	if (alloc_args(cmd, num_args, split) != 0)
		return (1);
	if (copy_args(cmd, split) != 0)
		return (1);
	return (0);
}
