/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:41:02 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/04/29 00:55:37 by ibarbouc         ###   ########.fr       */
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
