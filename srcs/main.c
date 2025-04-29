/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:58:04 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/04/30 01:03:40 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_commande	init(int ac, char **av, char **env)
{
	t_commande	command;

	command.env = env;
	command.av = av;
	command.pathname = get_cmd(&command);
	command.infile = av[1];
	command.outfile = av[ac - 1];
	command.len = ac - 3;
	command.pids = malloc(sizeof(pid_t) * command.len);
	return (command);
}

int	main(int ac, char **av, char **env)
{
	t_commande	command;

	(void)ac;
	command = init(ac, av, env);
	// create_child(&command);
	pipe_dad();
}
