/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:58:04 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/05/01 22:23:05 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_commande	init(int ac, char **av, char **env)
{
	t_commande	command;

	command.env = env;
	command.av = av;
	// command.pathname = get_cmd(&command);
	command.infile = av[1];
	command.outfile = av[ac - 1];
	command.len = ac - 3;
	// command.pids = malloc(sizeof(pid_t) * command.len);
	return (command);
}

int	main(int ac, char **av, char **env)
{
	t_commande	command;
	pid_t		child1;
	pid_t		child2;

	(void)ac;
	command = init(ac, av, env);
	pipe(command.pipefd);
	child1 = fork();
	if (child1 == 0)
	{
		first_child(&command);
	}
	child2 = fork();
	if (child2 == 0)
	{
		second_child(&command);
	}
	close(command.pipefd[0]);
	close(command.pipefd[1]);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
	return (0);
}
