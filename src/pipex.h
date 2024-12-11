/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:09:34 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/11 20:55:40 by joamiran         ###   ########.fr       */
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
# define TEMP_FILE ".heredoc_tmp"

typedef struct s_command
{
	char		*cmd;
	int			cmd_nr;
	char		**args;
	char		*path;
	pid_t		pid;
	int			fd[2];
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
void			ft_pipex(int argc, char **argv, char **envp);

// here_doc
void			handle_hd(char *limiter, int fd);
void			ft_here_doc(int argc, char **argv, char **envp);
int				setup_heredoc(char *limiter);
t_pipe			*piping_hd(int argc, char **argv, char **envp);
int				assign_commands_hd(t_pipe *pipex, char **argv);
t_pipe			*init_pipex_hd(int argc, char **argv, char **envp);
int				validation_hd(int argc, char **argv, char **envp);
int				assign_innoutfiles_hd(t_pipe *pipex, int argc, char **argv);

// pipe_utils
t_pipe			*piping(int argc, char **argv, char **envp);
int				make_pipes(t_pipe *pipex);
int				process_command(t_pipe *pipex, int cmd_index);
void			forking(t_pipe *pipex);
void			wait_for_children(t_pipe *pipex);
void			close_pipe(t_pipe *pipex, int cmd_index);
void			close_pipes(t_pipe *pipex);
void			close_correct_pipe(t_pipe *pipex, int cmd_index);
void			dup_handles(t_pipe *pipex, int cmd_index);
void			wait_for_children(t_pipe *pipex);

// security
int				is_valid_cmd_format(char *cmd);
int				check_for_here_doc(char *cmd);
int				validate_here_doc_format(int argc, char **argv);
int				validade_all_commands(int argc, char **argv);
int				validate_call(int argc, char **argv, char **envp);
int             check_file_permissions(int argc, char **argv);


// checkers
int				arg_check(int argc);
int				file_access_check(char *file);
int				params_check(int argc, char **argv);
int				assign_innoutfiles(t_pipe *pipex, int argc, char **argv);
char			*get_env_var(char **envp, const char *name);

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
int				count_args(char **split);
int				alloc_args(t_command *cmd, int num_args, char **split);
int				copy_args(t_command *cmd, char **split);

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
int				ft_flush(t_command *cmd, char **split);
// debug
void			print_info(t_pipe *pipex);
void			exit_error(t_pipe *pipex, char *msg);

#endif
