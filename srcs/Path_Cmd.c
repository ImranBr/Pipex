/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Path_Cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:36:19 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/05/05 19:20:53 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(t_commande *command)
{
	char	*path;
	char	**tab;
	int		i;

	if (!command->env)
		return (NULL);
	tab = NULL;
	i = 0;
	path = "PATH=";
	while (command->env && command->env[i])
	{
		if (ft_strncmp(command->env[i], path, 5) == 0)
		{
			tab = ft_split(command->env[i] + 5, ':');
			return (tab);
		}
		i++;
	}
	return (NULL);
}

char	*get_cmd(t_commande *command, char *s1)
{
	int		i;
	char	**str;
	char	*pathname;

	i = 0;
	if (!s1 || s1[0] == '\0')
		return (ft_putendl_fd("Command not found", STDERR_FILENO), NULL);
	if (s1[0] == '/')
	{
		if (access(s1, F_OK | X_OK) == 0)
			return (ft_strdup(s1));
		return (perror(s1), NULL);
	}
	str = get_path(command);
	if (!str)
		return (perror("PATH not found"), NULL);
	while (str[i])
	{
		pathname = ft_strjoin2(str[i], s1);
		if (pathname && access(pathname, F_OK | X_OK) == 0)
			return (free_split(str), pathname);
		free(pathname);
		i++;
	}
	return (free_split(str), perror(s1), NULL);
}
