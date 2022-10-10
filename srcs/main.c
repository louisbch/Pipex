/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:09:33 by lbouchon          #+#    #+#             */
/*   Updated: 2022/10/10 15:24:10 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac == 5)
	{
		ft_initialize_struct(&data, av);
		check_error(pipe(data.pfd));
		data.pid = fork();
		check_error(data.pid);
		if (data.pid == 0)
			first_child(data, envp);
		else
		{
			data.pid2 = fork();
			check_error(data.pid2);
			if (data.pid2 == 0)
				second_child(data, envp);
			parent_process(data);
		}
	}
	else
		write(2, "Try like this : ./pipex infile cmd1 cmd2 outfile", 71);
	return (0);
}
