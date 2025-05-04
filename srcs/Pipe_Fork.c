/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipe_Fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:36:30 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/05/05 00:53:38 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_commande *command)
{
	int		infile;
	char	*file;
	char	**cmd;

	cmd = ft_split(command->av[2], ' ');
	ft_check_cmd(cmd);
	close(command->pipefd[0]);
	infile = open(command->infile, O_RDONLY);
	if (infile < 0)
	{
		perror("infile");
		free_split(cmd);
		exit(EXIT_FAILURE);
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(command->pipefd[1], STDOUT_FILENO);
	close(command->pipefd[1]);
	file = get_cmd(command, cmd[0]);
	if (!file)
	{
		free_split(cmd);
		exit(EXIT_FAILURE);
	}
	execve(file, cmd, command->env);
	ft_failure(cmd, file);
}

void	middle_child(t_commande *command, char *cmd_str, int prev_pipe_read,
		int next_pipe_write)
{
	char	*file;
	char	**cmd;

	cmd = ft_split(cmd_str, ' ');
	if (!cmd || !cmd[0])
	{
		ft_putendl_fd("Command not found", STDERR_FILENO);
		if (cmd)
			free_split(cmd);
		exit(EXIT_FAILURE);
	}
	dup2(prev_pipe_read, STDIN_FILENO);
	close(prev_pipe_read);
	dup2(next_pipe_write, STDOUT_FILENO);
	close(next_pipe_write);
	file = get_cmd(command, cmd[0]);
	if (!file)
	{
		free_split(cmd);
		exit(EXIT_FAILURE);
	}
	execve(file, cmd, command->env);
	ft_failure(cmd, file);
}

void	last_child(t_commande *command)
{
	int		outfile;
	char	*file;
	char	**cmd;

	cmd = ft_split(command->av[3], ' ');
	ft_check_cmd(cmd);
	close(command->pipefd[1]);
	outfile = open(command->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
	{
		perror("outfile");
		free_split(cmd);
		exit(EXIT_FAILURE);
	}
	dup2(command->pipefd[0], STDIN_FILENO);
	close(command->pipefd[0]);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	file = get_cmd(command, cmd[0]);
	if (!file)
	{
		free_split(cmd);
		exit(EXIT_FAILURE);
	}
	execve(file, cmd, command->env);
	ft_failure(cmd, file);
}
