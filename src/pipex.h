/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:09:34 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/05 19:19:16 by joamiran         ###   ########.fr       */
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

# define HEREDOC "here_doc"
# define TEMP_FILE "/tmp/.heredoc_tmp"

typedef struct s_command
{
	char		*cmd;
	int			cmd_nr;
	char		**args;
	char		*path;
	pid_t		pid;
    int         fd[2];
	int			status;
}				t_command;

typedef struct s_pipex
{
	t_command	**cmds;
	int			n_cmds;
	pid_t		*pid;
	int			infile;
	int			outfile;

	char		**envp;
}				t_pipe;

typedef struct s_split_state
{
	char		**split;
	int			i;
	int			j;
}				t_split_state;

// main
int				main(int argc, char **argv, char **envp);
void            ft_pipex(int argc, char **argv, char **envp);

// here_doc
void       handle_hd(char *limiter, int fd);
void       ft_here_doc(int argc, char **argv, char **envp);

// pipe_utils
t_pipe          *piping(int argc, char **argv, char **envp);
int				make_pipes(t_pipe *pipex);
int				process_command(t_pipe *pipex, int cmd_index);
void            forking(t_pipe *pipex);
void			wait_for_children(t_pipe *pipex);
void			close_pipe(t_pipe *pipex, int cmd_index);
void            close_pipes(t_pipe *pipex);
void			close_correct_pipe(t_pipe *pipex, int cmd_index);
void            dup_handles(t_pipe *pipex, int cmd_index);
void            wait_for_children(t_pipe *pipex);


// checkers
int				arg_check(int argc);
int				file_access_check(char *file);
int				params_check(int argc, char **argv);
int				assign_innoutfiles(t_pipe *pipex, int argc, char **argv);

// parsing
int				count_commands(int argc);
int				set_commands(t_command *cmd, char *arg);
int				set_args(t_command *cmd, char *arg);
int				set_comnargs(t_command *cmd, char *arg);
int				is_space(char c);
int				is_quote(char c);
char			**ft_split2(char const *s, char c);
char			*ft_strjoin2(char *paths, char *cmd);
void			remove_quotes(char **s);

// init
char			*find_command(char *cmd, char **envp);
t_command		*new_command(void);
int				assign_commands(t_pipe *pipex, char **argv);
t_pipe			*init_pipex(int argc, char **argv, char **envp);
int				init_fds(t_pipe *pipex);

// free
void			free_split(char **split);
void			free_commands(t_pipe *pipex);
void			free_pipex(t_pipe *pipex);
void			clean_house(t_pipe *pipex);
// debug
void			print_info(t_pipe *pipex);
void            exit_error(t_pipe *pipex, char *msg);

#endif
