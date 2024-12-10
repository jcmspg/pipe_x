/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:19:27 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/10 21:50:10 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_valid_cmd_format(char *cmd)
{
	size_t	len;
	size_t	i;
	bool	is_valid;

	is_valid = false;
	if (!cmd || cmd[0] == '\0')
		return (1);
	len = ft_strlen(cmd);
	i = 0;
	while (i < len)
	{
		if (cmd[i] == '\n' || cmd[i] == '\t')
			return (1);
		if (cmd[i] != ' ')
			is_valid = true;
		i++;
	}
	if (!is_valid)
		return (1);
	return (0);
}

int	check_for_here_doc(char *cmd)
{
	if (ft_strncmp(cmd, "here_doc", 8) == 0)
		return (1);
	return (0);
}

int	validate_here_doc_format(int argc, char **argv)
{
	if (argc < 6)
	{
		ft_printf("Error: Invalid number of arguments.\n");
		ft_printf("Usage: %s here_doc LIMITER cmd1 ... cmdn file2\n", argv[0]);
		return (1);
	}
	return (0);
}

int	validade_all_commands(int argc, char **argv)
{
	int	i;

	i = 2;
	while (i <= argc - 1)
	{
		if (is_valid_cmd_format(argv[i]))
		{
			ft_printf("Error: Invalid command format\n");
			ft_printf("Usage: %s \"command\"\n", argv[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	validate_call(int argc, char **argv, char **envp)
{
	if (!envp || !*envp || envp[0] == NULL || envp[0][0] == '\0')
		return (ft_printf("Error: No environment\n"));
	if (argc < 4)
		return (ft_printf("Error: Not enough arguments\n"));
	if (validade_all_commands(argc, argv) != 0)
		return (1);
	return (0);
}
