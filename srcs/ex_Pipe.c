/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_Pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:58:35 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/04/30 01:08:49 by ibarbouc         ###   ########.fr       */
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

void	create_pipe(int pipefd[2])
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	write(STDOUT_FILENO, "Hello Pipe\n", 11);
	close(pipefd[1]);
	exit(EXIT_SUCCESS);
}

void	pipe_dad(void)
{
	int	pipefd[2];
	int	status;
	pid_t	pid;
	char	c;
	pid = fork();
	if (pid == 0)
		create_pipe(pipefd);
	else
	{
		close(pipefd[1]);
		while (read(pipefd[0], &c, 1) > 0)
			write(STDOUT_FILENO, &c, 1);
		close(pipefd[0]);
		waitpid(pid, &status, 0);
	}
}
