/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:09:33 by lbouchon          #+#    #+#             */
/*   Updated: 2022/10/04 14:40:27 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac == 5)
	{
		ft_initialize_struct(&data, av);
		if (pipe(data.pfd) == -1)
			exit(EXIT_FAILURE);
		data.pid = fork();
		if (data.pid < 0)
			exit(EXIT_FAILURE);
		if (data.pid == 0)
			first_child(data, envp);
		else
		{
			data.pid2 = fork();
			if (data.pid2 < 0)
				exit(EXIT_FAILURE);
			if (data.pid2 == 0)
				second_child(data, envp);
			parent_process(data);
		}
	}
	else
		write(2, "Try like this : ./pipex infile cmd1 cmd2 outfile", 71);
}
