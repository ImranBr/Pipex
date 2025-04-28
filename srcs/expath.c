/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expath.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:13:54 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/04/28 02:21:58 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

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
char	*ft_strjoin2(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	new_str = (char *)malloc(strlen(s1) + strlen(s2) + 2);
	if (!new_str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	new_str[i++] = '/';
	j = 0;
	while (s2[j] != '\0')
	{
		new_str[i++] = s2[j++];
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*get_cmd(char **av, char **env)
{
    int		i;
    int		j;
    char	**str;
    char    *pathname;
    
    i = 1;
    str = get_path(env);
    printf("%s\n", av[i]);
    j = 0;
    while (str[j])
    {
        pathname = ft_strjoin2(str[j], av[i]);
        if (access(pathname, F_OK | X_OK) == 0)
        {
            printf("commande trouvee");
            return (pathname);
        }
        j++;
    }
    printf("commande pas trouvee");
    return (NULL);
}
// {
//     int     i;
//     int     j;
//     char    **str;
//     char    *pathname;

//     i = 1;
//     j = 0;
    
//     // if (access(av[i], F_OK | X_OK) == 0)
//     //     return (av[i]);
//     str = get_path(env);
//     pathname = ft_strjoin2(str[j], av[i]);
//     while (str[j])
//     {
//         if (access(pathname, F_OK | X_OK))
//         {
//             printf("trouverrrr = %s\n\n\n", pathname);
//             return (pathname);
//         }
//         j++;
//     }
//     return (printf("pas trouver\n"), NULL);
// }

int	main(int ac, char **av, char **env)
{
    char *cmd;
	(void)ac;
    // (void)av;
    // get_path(env);
    cmd = get_cmd(av, env);
}
/*
./pipex infile cmd1 cmd2 outfile

./pipex infile ls cat outfile


/home/ibarbouc/.local/funcheck/host/cmd1
/home/ibarbouc/bin/cmd1
/usr/local/sbin/cmd1
/usr/local/bin/cmd1
/usr/sbin/cmd1
/usr/bin/cmd1
/sbin/cmd1
/bin/cmd1
/usr/games/cmd1
/usr/local/games/cmd1
/snap/bin/cmd1
➜  pipex git:(main) ✗ ./pipe


construire une fonction qui boucle sur toutes les string du path split
tester l'access sur chacunes des string modifier avec le nom de la commande a la fin
trouver le path et le stocker
*/