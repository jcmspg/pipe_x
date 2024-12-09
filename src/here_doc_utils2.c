/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:52:49 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/09 19:31:36 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_hd(char *limiter, int fd)
{
	char	*line;

	if (fd < 0)
		exit_error(NULL, "Error: cannot create temporary file");
	while (1)
	{
		ft_printf("heredoc> ");
		line = get_next_line(0);
		if (!line)
			exit(1);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
}

int	setup_heredoc(char *limiter)
{
	int	fd;

	fd = open(TEMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		exit_error(NULL, "Error: cannot create temporary file");
	handle_hd(limiter, fd);
    fd = open(TEMP_FILE, O_RDONLY);
	if (fd == -1)
	{
		unlink(TEMP_FILE);
		exit_error(NULL, "Error: cannot open temporary file");
	}
	return (fd);
}
