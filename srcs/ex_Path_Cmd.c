/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_Path_Cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:36:54 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/04/28 19:56:23 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "pipex.h"

char	**get_path(char **env)
{
	int		i;
	char	*str;
	char	*path;
	char	**tab;

	i = 0;
	// int j = 0;
	path = "PATH=";
	while (env[i])
	{
		if (ft_strncmp(env[i], path, 5) == 0)
			str = env[i];
		i++;
	}
	tab = ft_split(str + 5, ':');
	// while (tab[j])
	// {
	//     ft_printf("%s\n", tab[j]);
	//     j++;
	// }
	return (tab);
}

char	*get_cmd(char **av, char **env)
{
	int		i;
	int		j;
	char	**str;
	char	*pathname;

	i = 1;
	str = get_path(env);
	printf("%s\n", av[i]);
	j = 0;
	while (str[j])
	{
		pathname = ft_strjoin2(str[j], av[i]);
		if (access(pathname, F_OK | X_OK) == 0)
		{
			printf("commande trouvee\n");
			return (pathname);
		}
		j++;
	}
	perror(av[i]);
	return (NULL);
}

// // int	main(int ac, char **av, char **env)
// {
// 	// char	*cmd;

// 	(void)ac;
// 	// (void)av;
// 	// get_path(env);
// 	// cmd = 
// 	get_cmd(av, env);
// }

// ./pipex infile cmd1 cmd2 outfile

// ./pipex infile ls cat outfile

// /home/ibarbouc/.local/funcheck/host/cmd1
// /home/ibarbouc/bin/cmd1
// /usr/local/sbin/cmd1
// /usr/local/bin/cmd1
// /usr/sbin/cmd1
// /usr/bin/cmd1
// /sbin/cmd1
// /bin/cmd1
// /usr/games/cmd1
// /usr/local/games/cmd1
// /snap/bin/cmd1
// ➜  pipex git:(main) ✗ ./pipe

// construire une fonction qui boucle sur toutes les string du path split
// tester l'access sur chacunes des string modifier avec le nom de la commande a la fin
// trouver le path et le stocker