/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:43:24 by lbouchon          #+#    #+#             */
/*   Updated: 2022/10/07 15:53:42 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
void	check_error(int res)
{
	if (res == -1)
		ft_error();
}
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
	check_error(dup2(data.f1, STDIN_FILENO));
	check_error(dup2(data.pfd[1], STDOUT_FILENO));
	check_error(close(data.pfd[0]));
	check_error(close(data.pfd[1]));
	data.path_cmd1 = get_cmd_path(data.cmd1[0], envp);
	data.execv_cmd1 = execve(data.path_cmd1, data.cmd1, NULL);
	if (data.execv_cmd1 == -1)
		ft_error();
}

void	second_child(t_data data, char **envp)
{
	check_error(dup2(data.pfd[0], STDIN_FILENO));
	check_error(dup2(data.f2, STDOUT_FILENO));
	check_error(close(data.pfd[0]));
	check_error(close(data.pfd[1]));
	data.path_cmd2 = get_cmd_path(data.cmd2[0], envp);
	data.execv_cmd2 = execve(data.path_cmd2, data.cmd2, NULL);
	if (data.execv_cmd2 == -1)
		ft_error();
}

void	parent_process(t_data data)
{
	check_error(close(data.pfd[0]));
	check_error(close(data.pfd[1]));
	check_error(close(data.f1));
	check_error(close(data.f2));
	check_error(waitpid(data.pid, &data.status, 0));
	check_error(waitpid(data.pid2, &data.status, 0));
}
