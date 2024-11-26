/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:06:25 by joamiran          #+#    #+#             */
/*   Updated: 2024/11/26 21:00:14 by joamiran         ###   ########.fr       */
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


