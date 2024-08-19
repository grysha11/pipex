/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:01:16 by hzakharc          #+#    #+#             */
/*   Updated: 2024/08/19 16:27:33 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../include/ft_printf/ft_printf.h"
# include "../include/libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>

# define COLOR "\033[0m"
# define COLOR_RED "\033[1;31m"
# define COLOR_GREEN "\033[1;32m"
# define COLOR_BLUE "\033[1;34m"
# define COLOR_PURPLE "\033[1;35m"
# define COLOR_CYAN "\033[1;36m"

typedef struct s_list
{
	char			**value;
	struct s_list	*next;
}				t_list;

typedef struct s_pipex
{
	char	*file1;
	char	*file2;
	t_list	*cmd;
}				t_pipex;

void	error_message(char *str);
void	free_data(t_pipex *data);
void	error_data(t_pipex *data, char *str);
void	ft_lst_clear(t_list **lst);
void	ft_free_matrix(char **matrix);

#endif