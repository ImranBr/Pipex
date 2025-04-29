/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:32:10 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/04/30 01:04:31 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_commande
{
	char	**env;
	char	**av;
	char	*pathname;
	pid_t	*pids;
	char	*infile;
	char	*outfile;
	int		len;
}			t_commande;

char		*ft_strjoin2(char const *s1, char const *s2);
char		*get_cmd(t_commande *command);
char		**get_path(t_commande *command);
void		create_child(t_commande *command);
void	pipe_dad(void);

#endif