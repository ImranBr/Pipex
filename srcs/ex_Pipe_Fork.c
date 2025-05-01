/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_Pipe_Fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:58:35 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/05/02 01:07:08 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_commande *command)
{
	int		infile;
	char	*file;
	char	**cmd;

	file = NULL;
	cmd = ft_split(command->av[2], ' ');
	if (!cmd)
		free_split(cmd);
	close(command->pipefd[0]);
	infile = open(command->infile, O_RDONLY);
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(command->pipefd[1], STDOUT_FILENO);
	close(command->pipefd[1]);
	file = get_cmd(command, cmd[0]);
	execve(file, cmd, command->env);
	perror("Execve Failure1");
	free_split(cmd);
	exit(EXIT_FAILURE);
}

void	second_child(t_commande *command)
{
	int		outfile;
	char	*file;
	char	**cmd;

	cmd = ft_split(command->av[3], ' ');
	file = get_cmd(command, cmd[0]);
	close(command->pipefd[1]);
	outfile = open(command->outfile, O_WRONLY);
	dup2(command->pipefd[0], STDIN_FILENO);
	close(command->pipefd[0]);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execve(file, cmd, command->env);
	perror("Execve Failure2");
	free_split(cmd);
	exit(EXIT_FAILURE);
}
