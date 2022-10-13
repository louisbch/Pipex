/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:09:33 by lbouchon          #+#    #+#             */
/*   Updated: 2022/10/13 15:36:24 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free_strs(char **strs, char *str)
{
	int	i;

	if (strs)
	{
		i = 0;
		while (strs[i])
		{
			free(strs[i]);
			strs[i] = NULL;
		}
		free(strs);
		strs = NULL;
	}
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_putendl(char *str)
{
	ft_putstr(str);
	ft_putchar(10);
}

void	ft_check_command(char **av, char **envp)
{
	int		error;
	char	*cmd_path;
	char	**cmd_options;

	error = 0;
	cmd_options = ft_split(av[2], ' ');
	cmd_path = get_cmd_path(cmd_options[0], envp);
	if (!cmd_path)
	{
		ft_putstr("Command not found : ");
		ft_putendl(cmd_options[0]);
		error++;
	}
	ft_free_strs(cmd_options, cmd_path);
	cmd_options = ft_split(av[3], ' ');
	cmd_path = get_cmd_path(cmd_options[0], envp);
	if (!cmd_path)
	{
		ft_putstr("Command not found : ");
		ft_putendl(cmd_options[0]);
		error++;
	}
	ft_free_strs(cmd_options, cmd_path);
	if (error > 0)
		exit(1);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac == 5)
	{
		ft_initialize_struct(&data, av);
		ft_check_command(av, envp);
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
		write(2, "Try like this : ./pipex infile cmd1 cmd2 outfile\n", 49);
	return (0);
}
