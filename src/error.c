/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:34:11 by hzakharc          #+#    #+#             */
/*   Updated: 2024/08/19 16:27:42 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_lst_clear(t_list **lst)
{
	t_list	*head;

	while (*lst)
	{
		head = (*lst)->next;
		ft_free_matrix((*lst)->value);
		free(*lst);
		(*lst) = head;
	}
}

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
		if (data->cmd)
			ft_lst_clear(&data->cmd);
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
