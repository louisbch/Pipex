/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:24:40 by lbouchon          #+#    #+#             */
/*   Updated: 2022/10/10 12:51:32 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**find_and_split_path(char **envp)
{
	char	*env_path;
	char	**paths;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			env_path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			break ;
		}
		i++;
	}
	paths = ft_split(env_path, ':');
	return (paths);
	free(env_path);
}

int	ft_is_path(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '/')
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (1);
	}
	return (0);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*cmd_path;
	int		i;

	if (!cmd)
		ft_error();
	paths = find_and_split_path(envp);
	i = 0;
	while (paths[i])
	{
		if (ft_is_path(cmd) == 1)
			return (cmd);
		paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free (cmd_path);
		i++;
	}
	return (NULL);
}

char	**secure_cmd(char *str)
{
	if (!str)
		return (NULL);
	return (ft_split(str, ' '));
}
