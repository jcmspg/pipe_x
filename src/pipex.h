/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:09:34 by joamiran          #+#    #+#             */
/*   Updated: 2024/11/27 20:44:03 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../inc/lib_ft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_fd
{
	int			fd[2];
}				t_fd;

typedef struct s_command
{
	char		*cmd;
	char		**args;
	char		*path;
	int			*pid;
	bool		done;
	t_fd		*fd;
}				t_command;

typedef struct s_pipex
{
	t_command	**cmds;
	int			n_cmds;
	int			*pid;
	int			infile;
	int			outfile;

	char		**envp;
}				t_pipe;

// main
int				main(int argc, char **argv, char **envp);

// pipe
int             make_pipe(t_pipe *pipex);



// checkers
int				arg_check(int argc);
int				file_access_check(char *file);
int				params_check(int argc, char **argv);
int				assign_innoutfiles(t_pipe *pipex, int argc, char **argv);

// parsing
int				count_commands(int argc);
int				set_comnargs(t_command *cmd, char *arg);

char			*ft_strjoin2(char *paths, char *cmd);

// init
char			*find_command(char *cmd, char **envp);
t_command		*new_command(void);
int				assign_commands(t_pipe *pipex, char **argv);
t_pipe			*init_pipex(int argc, char **argv, char **envp);

// free
void			free_split(char **split);
void			free_commands(t_pipe *pipex);
void			free_pipex(t_pipe *pipex);

#endif
