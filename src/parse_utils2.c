/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:28:13 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/03 18:41:31 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

void	remove_quotes(char **split)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (split[i])
	{
		len = strlen(split[i]);
		if (len > 1 && is_quote(split[i][0]) && split[i][0] == split[i][len
			- 1])
		{
			j = 1;
			while (j < len - 1)
			{
				split[i][j - 1] = split[i][j];
				j++;
			}
			split[i][len - 2] = '\0';
		}
		i++;
	}
}
