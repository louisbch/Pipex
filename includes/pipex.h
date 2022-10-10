/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:57:21 by lbouchon          #+#    #+#             */
/*   Updated: 2022/10/10 15:13:01 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>

typedef struct s_data
{
	char	**cmd1;
	char	**cmd2;
	int		pfd[2];
	int		f1;
	int		f2;
	int		pid;
	int		pid2;
	char	*path_cmd1;
	char	*path_cmd2;
	int		status;
	int		execv_cmd1;
	int		execv_cmd2;
}				t_data;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**find_and_split_path(char **envp);
char	*get_cmd_path(char *cmd, char **envp);
void	pipex(t_data data, char **av);
void	first_child(t_data data, char **av);
void	second_child(t_data data, char **av);
void	parent_process(t_data data);
void	ft_initialize_struct(t_data *data, char **av);
char	**secure_cmd(char *str);
int		ft_is_path(char *cmd);
void	check_error(int res);
void	ft_cmd_not_exist(char *path_cmd, char **cmd);

#endif