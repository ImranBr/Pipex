/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:58:04 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/05/05 19:18:17 by ibarbouc         ###   ########.fr       */
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
	command.len = ac - 3;
	command.pids = malloc(sizeof(pid_t) * command.len);
	if (!command.pids)
	{
		ft_putendl_fd("malloc failed", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (command);
}

int	main(int ac, char **av, char **env)
{
	t_commande	command;
	int			i;

	if (ac < 5)
		return (ft_putstr_fd("Error: number of arguments", 2), EXIT_FAILURE);
	command = init(ac, av, env);
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
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_commande	command;
// 	int			**pipes;
// 	pid_t		pid;
// 	int			i;
// 	int			j;

// 	if (ac < 5)
// 		return (ft_putendl_fd("Error: Not enough arguments\n", 2),
// 			EXIT_FAILURE);
// 	command = init(ac, av, env);
// 	pipes = create_pipes(command.len - 1);
// 	if (!pipes)
// 		return (free(command.pids), EXIT_FAILURE);
// 	i = 0;
// 	while (i < command.len)
// 	{
// 		pid = fork();
// 		if (pid < 0)
// 		{
// 			perror("fork");
// 			free_pipes(pipes, command.len - 1);
// 			free(command.pids);
// 			exit(EXIT_FAILURE);
// 		}
// 		else if (pid == 0)
// 		{
// 			j = 0;
// 			if (i == 0)
// 			{
// 				// Premier enfant : ne garde que pipes[0][1]
// 				while (j < command.len - 1)
// 				{
// 					if (j != 0)
// 					{
// 						close(pipes[j][0]);
// 						close(pipes[j][1]);
// 					}
// 					j++;
// 				}
// 				command.pipefd[0] = pipes[0][0];
// 				command.pipefd[1] = pipes[0][1];
// 				first_cmd(&command);
// 			}
// 			else if (i == command.len - 1)
// 			{
// 				// Dernier enfant : ne garde que pipes[i-1][0]
// 				while (j < command.len - 1)
// 				{
// 					if (j != i - 1)
// 					{
// 						close(pipes[j][0]);
// 						close(pipes[j][1]);
// 					}
// 					j++;
// 				}
// 				command.pipefd[0] = pipes[i - 1][0];
// 				command.pipefd[1] = pipes[i - 1][1];
// 				last_cmd(&command, av[2 + i]);
// 			}
// 			else
// 			{
// 				// Enfant du milieu : garde pipes[i-1][0] et pipes[i][1]
// 				while (j < command.len - 1)
// 				{
// 					if (j != i - 1)
// 						close(pipes[j][0]);
// 					if (j != i)
// 						close(pipes[j][1]);
// 					j++;
// 				}
// 				middle_cmd(&command, av[2 + i], pipes[i - 1][0], pipes[i][1]);
// 			}
// 		}
// 		// Parent continue
// 		command.pids[i] = pid;
// 		i++;
// 	}
// 	// Parent ferme tous les tuyaux
// 	close_pipes(pipes, command.len - 1);
// 	// Parent attend tous les enfants
// 	i = 0;
// 	while (i < command.len)
// 		waitpid(command.pids[i++], NULL, 0);
// 	// Nettoyage
// 	free_pipes(pipes, command.len - 1);
// 	free(command.pids);
// 	return (0);
// }
