/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:41:02 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/04/28 19:57:55 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_fork(char **av, char **env)
{
	int		status;
	char	*pathname;
	pid_t	pid;
	char	**tab;

	tab = av;
	pathname = get_cmd(tab, env);
	// printf("pathname == %s\n", pathname);
	pid = fork();
	printf("pid == %d\n", pid);
	if (pid == -1)
		perror("fork failure");
	else if (pid == 0)
	{
		printf("tour2\n");
		printf("cmd to find == %s\n", pathname);
		printf("tab[1] == %s\n", tab[1]);
		// execve(pathname, &tab[1], env);
		if (execve(pathname, &tab[1], env) == -1)
			perror("execve failure");
	}
	else
	{
		printf("tour 1\n");
		waitpid(pid, &status, 0);
	}
}


// void create_fork(char *cmd, char **av, char **env)
// {
//     int     status;
//     pid_t   pid;

//     pid = fork();
//     if (pid == -1)
//         perror("fork failure");
//     else if (pid == 0)
//     {
//         execve(cmd, av, env); ===> execve ne retourne rien si elle reussi,
	//retour uniquement quand elle echoue
//         perror("execve failure");
//     }
//     else
//         waitpid(pid, &status, 0);
// }