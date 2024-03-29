/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 22:08:31 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/01/05 23:33:02 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_find_path(t_pipex *pipex, char *command, char **envp)
{
	int		i;
	char	*tmp;
	char	*exec_cmd;

	i = 0;
	while (pipex->paths && pipex->paths[i])
	{
		tmp = ft_strjoin(pipex->paths[i], "/");
		exec_cmd = ft_strjoin(tmp, command);
		free(tmp);
		if (access(exec_cmd, F_OK | X_OK) == 0)
			return (exec_cmd);
		free(exec_cmd);
		i++;
	}
	return (command);
}

void	ft_exe(char *path, t_pipex pipex, char **envp, int flag)
{
	char	**splited_cmd;
	int		ret;

	if (!flag)
		splited_cmd = pipex.s_cmd1;
	else
		splited_cmd = pipex.s_cmd2;
	//exit(printf("path : %s\nsplited_cmd[0] : %s\n", path, splited_cmd[0]));
	ret = execve(path, splited_cmd, envp);
	if (ret == -1)
	{
		ft_error("pipex: command not found: ");
		ft_error(splited_cmd[0]);
		exit(ft_error("\n"));
	}
}

void	ft_child2(char *outfile, int *fd, char **envp, t_pipex *pipex)
{
	int		file;
	char	*path;
	int		pid;
	int		fdf[2];

	pipe(fdf);
	file = ft_open(outfile, WRITE);
	close(fd[1]);
	dup2(file, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	path = ft_find_path(pipex, pipex->s_cmd2[0], envp);
	pid = fork();
	if (pid == CHILD)
		ft_exe(path, *pipex, envp, 1);
}

void	ft_child1(char *infile, int *fd, char **envp, t_pipex *pipex)
{
	int		file;
	char	*path;

	file = ft_open(infile, READ);
	close(fd[0]);
	dup2(file, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	path = ft_find_path(pipex, pipex->s_cmd1[0], envp);
	ft_exe(path, *pipex, envp, 0);
}
