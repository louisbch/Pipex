/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:43:24 by lbouchon          #+#    #+#             */
/*   Updated: 2022/10/04 18:40:03 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_initialize_struct(t_data *data, char **av)
{
	data->cmd1 = secure_cmd(av[2]);
	data->cmd2 = secure_cmd(av[3]);
	data->f1 = open(av[1], O_RDONLY);
	if (data->f1 == -1)
		ft_error();
	data->f2 = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->f2 == -1)
		ft_error();
}

void	first_child(t_data data, char **envp)
{
	dup2(data.f1, STDIN_FILENO);
	dup2(data.pfd[1], STDOUT_FILENO);
	close(data.pfd[0]);
	close(data.pfd[1]);
	data.path_cmd1 = get_cmd_path(data.cmd1[0], envp);
	if (execve(data.path_cmd1, data.cmd1, NULL) == -1)
		ft_error();
}

void	second_child(t_data data, char **envp)
{
	dup2(data.pfd[0], STDIN_FILENO);
	dup2(data.f2, STDOUT_FILENO);
	close(data.pfd[0]);
	close(data.pfd[1]);
	data.path_cmd2 = get_cmd_path(data.cmd2[0], envp);
	if (execve(data.path_cmd2, data.cmd2, NULL) == -1)
		ft_error();
}

void	parent_process(t_data data)
{
	close(data.pfd[0]);
	close(data.pfd[1]);
	close(data.f1);
	close(data.f2);
	waitpid(data.pid, &data.status, 0);
	waitpid(data.pid2, &data.status, 0);
}

char	**secure_cmd(char *str)
{
	if (!str)
		return (NULL);
	return (ft_split(str, ' '));
}
