/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:09:33 by lbouchon          #+#    #+#             */
/*   Updated: 2022/09/07 17:01:47 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	char	**paths;
	char	*cmd;
	char	*cmd_path;
	
	cmd = "ls";
	paths = find_and_split_path(envp);
	cmd_path = get_cmd_path(cmd, envp);
	printf("%s", cmd_path);
	return (0);
}
