/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_Path_Cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:36:54 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/05/02 01:06:33 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(t_commande *command)
{
	char	*path;
	char	**tab;
	int		i;

	tab = NULL;
	i = 0;
	path = "PATH=";
	while (command->env[i])
	{
		if (ft_strncmp(command->env[i], path, 5) == 0)
		{
			tab = ft_split(command->env[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (tab);
}

char	*get_cmd(t_commande *command, char *s1)
{
	int		i;
	char	**str;
	char	*pathname;

	i = 0;
	str = get_path(command);
	if (!str)
		return (perror("PATH not found"), NULL);
	while (str[i])
	{
		pathname = ft_strjoin2(str[i], s1);
		if (pathname)
		{
			if (access(pathname, F_OK | X_OK) == 0)
			{
				free_split(str);
				return (pathname);
			}
			free(pathname);
		}
		i++;
	}
	return (free_split(str), perror(s1), NULL);
}
