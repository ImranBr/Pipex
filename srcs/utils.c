/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:17:34 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/05/06 01:55:43 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	ft_failure(char **cmd, char *file)
{
	perror("Execve Failure");
	if (cmd)
		free_split(cmd);
	if (file)
		free(file);
	exit(EXIT_FAILURE);
}

void	ft_check_cmd(char **cmd)
{
	if (!cmd)
	{
		ft_putendl_fd("Malloc error for command", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (!cmd[0])
	{
		ft_putendl_fd("Command not found", STDERR_FILENO);
		free_split(cmd);
		exit(EXIT_FAILURE);
	}
}
