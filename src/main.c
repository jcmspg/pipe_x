/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:27:20 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/11 17:45:45 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (validate_call(argc, argv, envp) != 0)
		return (1);
	if (check_for_here_doc(argv[1]) == 1)
	{
		if (validate_here_doc_format(argc, argv) != 0)
			return (1);
		ft_here_doc(argc, argv, envp);
	}
	else
		ft_pipex(argc, argv, envp);
	return (0);
}
