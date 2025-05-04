/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:58:04 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/05/05 00:52:49 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

t_commande	init(int ac, char **av, char **env)
{
	t_commande	command;

	command.env = env;
	command.av = av;
	command.infile = av[1];
	command.outfile = av[ac - 1];
	command.len = ac - 3;
	return (command);
}

int	main(int ac, char **av, char **env)
{
	t_commande	command;
	pid_t		child1;
	pid_t		child2;

	if (ac != 5)
		return (ft_putstr_fd("Error: number of arguments", 2), EXIT_FAILURE);
	command = init(ac, av, env);
	pipe(command.pipefd);
	child1 = fork();
	if (child1 == 0)
		first_child(&command);
	child2 = fork();
	if (child2 == 0)
		last_child(&command);
	close(command.pipefd[0]);
	close(command.pipefd[1]);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
	return (0);
}
