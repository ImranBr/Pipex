/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:32:10 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/05/05 00:53:14 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_commande
{
	int		pipefd[2];
	char	**env;
	char	**av;
	char	*pathname;
	pid_t	*pids;
	char	*infile;
	char	*outfile;
	int		len;
}			t_commande;

char		*ft_strjoin2(char const *s1, char const *s2);
char		*get_cmd(t_commande *command, char *s1);
char		**get_path(t_commande *command);
void		first_child(t_commande *command);
void		last_child(t_commande *command);
void		middle_child(t_commande *command, char *cmd_str, int prev_pipe_read,
				int next_pipe_write);
void		ft_failure(char **cmd, char *file);
void		ft_check_cmd(char **cmd);

// void	close_all_pipes(int **pipes, int n_pipes);
// void	free_pipes(int **pipes, int n_pipes);
// int	**create_pipes(int n_pipes);
// void	execute_first_cmd(t_commande *command, int **pipes);
// void	execute_middle_cmd(t_commande *command, int **pipes, int i);
// void	execute_last_cmd(t_commande *command, int **pipes, int last_pipe_index);
// char		*ft_strjoin2(char const *s1, char const *s2);
// char		*get_cmd(t_commande *command, char *s1);
// char		**get_path(t_commande *command);
// void		ft_failure(char **cmd, char *file);

#endif