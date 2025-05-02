/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_Pipe_Fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:58:35 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/05/02 20:05:48 by ibarbouc         ###   ########.fr       */
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
	if (!cmd || !cmd[0])
	{
		perror("Invalid command");
		if (cmd)
			free_split(cmd);
		exit(EXIT_FAILURE);
	}
	close(command->pipefd[0]);
	infile = open(command->infile, O_RDONLY);
	if (infile < 0)
	{
		perror("Erreur ouverture infile");
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
	perror("Execve Failure1");
	free_split(cmd);
	free(file);
	exit(EXIT_FAILURE);
}

void	second_child(t_commande *command)
{
	int		outfile;
	char	*file;
	char	**cmd;

	cmd = ft_split(command->av[3], ' ');
	if (!cmd || !cmd[0])
	{
		perror("Invalid command");
		if (cmd)
			free_split(cmd);
		exit(EXIT_FAILURE);
	}
	close(command->pipefd[1]);
	outfile = open(command->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
	perror("Execve Failure2");
	free_split(cmd);
	free(file);
	exit(EXIT_FAILURE);
}
