/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:06:25 by joamiran          #+#    #+#             */
/*   Updated: 2024/11/27 21:07:14 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



// pipex "file1" "cmd1" "cmd2" ... "cmdn" "file2"
// 0      1       2      3           n-1     n
//
int count_commands(int argc)
{
    int n_cmds;
    n_cmds = argc - 3;

    return (n_cmds);
}

int set_comnargs(t_command *cmd, char *arg)
{
    char *command;
    char **args;
    char **split;

    split = ft_split(arg, ' ');
    if (!split)
        return (1);
    command = split[0];
    
    if (split[1])
        args = split + 1;
    else
        args = NULL;
   
    cmd->args = args;
    
    if (args)
    {
        ft_printf("args: ");
        while (*args)
        {
            ft_printf("%s ", *args);
            args++;
        }
        ft_printf("\n");
    }

    ft_printf("command: %s\n", command);

    cmd->cmd = ft_strdup(command);
    if (!cmd->cmd)
    {
        free_split(split);
        return (1);
    }    

    free_split(split);
    // print the command and its arguments
    return (0);
}

