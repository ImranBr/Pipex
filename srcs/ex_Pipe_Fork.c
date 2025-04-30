/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_Pipe_Fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:58:35 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/04/30 20:57:13 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_child(t_commande *command)
{
	int		status;
	pid_t	pid;
	char	**tab;

	tab = command->av;
	command->pathname = get_cmd(command);
	pid = fork();
	printf("pid == %d\n", pid);
	if (pid == -1)
		perror("fork failure");
	else if (pid == 0)
	{
		printf("tour2\n");
		printf("cmd to find == %s\n", command->pathname);
		printf("tab[1] == %s\n", tab[1]);
		if (execve(command->pathname, &tab[1], command->env) == -1)
			perror("execve failure");
	}
	else
	{
		printf("tour 1\n");
		waitpid(pid, &status, 0);
	}
}

void	first_child(t_commande *command)
{
	int		infile;
	
	close(command->pipefd[0]);
	infile = open(command->infile, O_RDONLY);
	// if (!infile)
	// {
	// 	perror("Infile ko");
	// 	exit(1);	
		
	// }
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(command->pipefd[1], STDOUT_FILENO);
	close(command->pipefd[1]);
	int i = 0;
	while (command->av[i])
	{
		printf("%s\n %s\n", command->pathname, command->av[i]);
		i++;
	}
	execve(command->pathname, command->av, command->env);
	perror("Execve Failure");
	exit(EXIT_FAILURE);
}

void	second_child(t_commande *command)
{
	int		outfile;

	close(command->pipefd[1]);
	outfile = open(command->outfile, O_WRONLY);
	// if (!outfile)
	// {
	// 	perror("Outfile ko");
	// 	exit(1);	

	// }
	dup2(command->pipefd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	close(command->pipefd[0]);
	int i = 0;
	while (command->av[i])
	{
		printf("%s\n %s\n", command->pathname, command->av[i]);
		i++;
	}
	execve(command->pathname, command->av, command->env);
	perror("Execve Failure");
	exit(EXIT_FAILURE);
}

// void	pipe_dad(void)
// {
	// int	pipefd[2];
	// int	status;
	// pid_t	pid;
	// char	c;
	// 
	// pid = fork();
	// if (pid == 0)
		// first_child();
	// else
	// {
		// close(pipefd[1]);
		// while (read(pipefd[0], &c, 1) > 0)
		// 	write(STDOUT_FILENO, &c, 1);
		// close(pipefd[0]);
		// waitpid(pid, &status, 0);
	// }
// }
// ./pipex infile ls -l wc -l outfile