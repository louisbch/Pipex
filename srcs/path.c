/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:24:40 by lbouchon          #+#    #+#             */
/*   Updated: 2022/11/04 15:31:11 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	return (str);
}

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
	if (env_path)
		free(env_path);
	return (paths);
}

char	**join_paths(char **envp)
{
	char	**paths;
	char	*tmp;
	int		i;

	paths = find_and_split_path(envp);
	i = -1;
	while (paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(tmp, "/");
		ft_free_strs (NULL, tmp);
	}
	return (paths);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*cmd_path;
	char	*tmp;
	int		i;

	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	paths = join_paths(envp);
	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			ft_free_strs(paths, NULL);
			return (cmd_path);
		}
		free(cmd_path);
	}
	ft_free_strs(paths, NULL);
	return (NULL);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
