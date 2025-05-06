/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:58:04 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/05/06 02:14:49 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

t_commande	init(int ac, char **av, char **env)
{
	t_commande	command;

	command.env = env;
	command.av = av;
	command.fd_tmp = -1;
	command.infile = av[1];
	command.outfile = av[ac - 1];
	// command.len = ac - 3;
	return (command);
}
void	cleanup_and_exit(t_commande *command, int status)
{
	if (command->pipefd[0] != -1)
		close(command->pipefd[0]);
	if (command->pipefd[1] != -1)
		close(command->pipefd[1]);
	if (command->fd_tmp != -1)
		close(command->fd_tmp);
	exit(status);
}

int	main(int ac, char **av, char **env)
{
	t_commande	command;
	int			i;

	if (ac < 5)
		return (ft_putstr_fd("Error: number of arguments", 2), EXIT_FAILURE);
	command = init(ac, av, env);
	printf("!!!!!! name av[1] = %s  et name infile = %s\n", av[1], command.infile);
	i = 2;
	while (i)
	{
		if (i == 2)
			first_cmd(&command);
		else if (i == (ac - 2))
		{
			last_cmd(&command, i);
			break ;
		}
		else
			middle_cmd(&command, command.av[i]);
		i++;
	}
	cleanup_and_exit(&command, 0);
	return (0);
}
