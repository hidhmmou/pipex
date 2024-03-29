/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:32:56 by hidhmmou          #+#    #+#             */
/*   Updated: 2022/12/12 23:37:55 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ;
	while (*str)
		write(fd, str++, 1);
}

int	ft_error(char *message)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(RESET, 2);
	return (1);
}

int	ft_open(char *file, int x)
{
	int	fd;

	fd = 0;
	if (x == READ)
		fd = open(file, O_RDONLY);
	else if (x == HERE_DOC)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (x == WRITE)
		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
	{
		ft_error(ft_strjoin("pipex: no such file or directory: ", file));
		exit(ft_error("\n"));
	}
	return (fd);
}

char	*ft_get_paths_line(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A'
			&& env[i][2] == 'T' && env[i][3] == 'H')
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

void	ft_init(t_pipex *pipex, char *cmd1, char **env)
{
	pipex->splited_cmd = ft_split(cmd1, ' ');
	pipex->paths_line = ft_get_paths_line(env);
	pipex->paths = ft_split(pipex->paths_line, ':');
}
//close(file); line = 76