/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipe_Fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:36:30 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/05/06 02:21:16 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_cmd(t_commande *command)
{
	int		fd_infile;
	char	*file;
	char	**cmd;
	pid_t	child;

	if (pipe(command->pipefd) == -1)
	{
		perror("pipe ko");
		exit(EXIT_FAILURE);
	}
	cmd = ft_split(command->av[2], ' ');
	printf(" infile name : %s\n", command->infile);
	
	fd_infile = open(command->infile, O_RDONLY);
	if (fd_infile < 0)
	{
		perror("infile");
		free_split(cmd);
		exit(EXIT_FAILURE);
	}
	child = fork();
	if (child == 0)
	{
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
		dup2(command->pipefd[1], STDOUT_FILENO);
		close(command->pipefd[1]);
		close(command->pipefd[0]);
		ft_check_cmd(cmd);
		file = get_cmd(command, cmd[0]);
		if (!file)
		{
			perror("aie");
			free_split(cmd);
			exit(EXIT_FAILURE);
		}
		execve(file, cmd, command->env);
		// close(command->pipefd[0]);
		// close(command->pipefd[1]);
		ft_failure(cmd, file);
	}
	close(fd_infile);
	close(command->pipefd[1]);
	free_split(cmd);
	command->fd_tmp = command->pipefd[0];
	command->pipefd[1] = -1;
	command->pipefd[0] = -1;
}

void	middle_cmd(t_commande *command, char *cmd_str)
{
	char	*file;
	char	**cmd;
	pid_t	child;

	if (pipe(command->pipefd) == -1)
	{
		perror("pipe ko");
		exit(EXIT_FAILURE);
	} // return -1 ??? tiakonpri
	cmd = ft_split(cmd_str, ' ');
	child = fork();
	if (child == 0)
	{
		dup2(command->fd_tmp, STDIN_FILENO);
		close(command->fd_tmp);
		dup2(command->pipefd[1], STDOUT_FILENO);
		close(command->pipefd[1]);
		close(command->pipefd[0]);
		ft_check_cmd(cmd);
		file = get_cmd(command, cmd[0]);
		if (!file)
		{
			free_split(cmd);
			exit(EXIT_FAILURE);
		}
		execve(file, cmd, command->env);
		ft_failure(cmd, file);
	}
	close(command->pipefd[1]);
	close(command->fd_tmp);
	free_split(cmd);
	command->fd_tmp = command->pipefd[0];
	command->pipefd[1] = -1;
	command->pipefd[0] = -1;
}

void	last_cmd(t_commande *command, int i)
{
	int		fd_outfile;
	char	*file;
	char	**cmd;
	pid_t	child;
	
	cmd = ft_split(command->av[i], ' ');
	fd_outfile = open(command->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_outfile < 0)
	{
		perror("outfile");
		free_split(cmd);
		exit(EXIT_FAILURE);
	}
	child = fork();
	if (child == 0)
	{
		dup2(command->fd_tmp, STDIN_FILENO);
		close(command->fd_tmp);
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd_outfile);
		ft_check_cmd(cmd);
		file = get_cmd(command, cmd[0]);
		if (!file)
		{
			perror("aie2");
			free_split(cmd);
			exit(EXIT_FAILURE);
		}
		execve(file, cmd, command->env);
		ft_failure(cmd, file);
	}
	free_split(cmd);
	close(fd_outfile);
	close(command->fd_tmp);
	while (waitpid(-1, NULL, 0) != -1)
		;
}
