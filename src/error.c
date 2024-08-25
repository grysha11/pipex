/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:34:11 by hzakharc          #+#    #+#             */
/*   Updated: 2024/08/25 13:39:08 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix)
	{
		while (matrix[i] != NULL)
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
}

void	free_data(t_pipex *data)
{
	if (data)
	{
		if (data->cmd1)
			ft_free_matrix(data->cmd1);
		if (data->cmd2)
			ft_free_matrix(data->cmd2);
		if (data->file1)
			free(data->file1);
		if (data->file2)
			free(data->file2);
		free(data);
	}
}

void	error_data(t_pipex *data, char *str)
{
	free_data(data);
	error_message(str);
	exit(1);
}

void	error_message(char *str)
{
	ft_putstr_fd(COLOR_RED, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(COLOR, 2);
}
