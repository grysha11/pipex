/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:17:41 by hzakharc          #+#    #+#             */
/*   Updated: 2024/08/21 14:09:57 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_args(t_pipex *data)
{
	if (access(data->cmd1[0], X_OK) == -1)
		error_data(data, "INCORRECT COMMAND\n");
	if (access(data->cmd2[0], X_OK) == -1)
		error_data(data, "INCORRECT COMMAND\n");
	if (access(data->file1, R_OK) == -1)
		error_data(data, "CANNOT OPEN INFILE\n");
	data->fd[0] = open(data->file1, O_RDONLY);
	data->fd[1] = open(data->file2, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (access(data->file2, W_OK) == -1)
		error_data(data, "CANNOT OPEN OUTFILE\n");
}

void	check_fds(int pipefd[], t_pipex *data)
{
	if (pipefd[0] > 0)
		close(pipefd[0]);
	if (pipefd[1] > 0)
		close(pipefd[1]);
	if (data->fd[0] > 0)
		close(data->fd[0]);
	if (data->fd[1] > 0)
		close(data->fd[1]);
}
