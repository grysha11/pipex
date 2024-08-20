/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:26:34 by hzakharc          #+#    #+#             */
/*   Updated: 2024/08/20 17:26:03 by hzakharc         ###   ########.fr       */
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
		error_data(data, "INFILE IS NOT FOUND\n");
	data->fd[0] = open(data->file1, O_RDONLY);
	data->fd[1] = open(data->file2, O_WRONLY | O_TRUNC | O_CREAT, 0644);
}

void	execute_util(t_pipex *data, char **envp, int pipefd[])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_data(data, "FORK ERROR\n");
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		dup2(data->fd[1], STDOUT_FILENO);
		execve(data->cmd2[0], data->cmd2, envp);
		error_data(data, "EXECUTION FAILURE\n");
	}
	waitpid(pid, 0, 0);
}

void	pipex(t_pipex *data, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		error_data(data, "PIPE ERROR\n");
	pid = fork();
	if (pid == -1)
		error_data(data, "FORK ERORR\n");
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		dup2(data->fd[0], STDIN_FILENO);
		execve(data->cmd1[0], data->cmd1, envp);
		error_data(data, "EXECUTION FAILURE\n");
	}
	waitpid(pid, 0, 0);
	execute_util(data, envp, pipefd);
	waitpid(pid, 0, 0);
	close(pipefd[0]);
	close(pipefd[1]);
}

void print_data(t_pipex *data)
{
    int i;

    printf("File 1: %s\n", data->file1);
    printf("File 2: %s\n", data->file2);

    printf("Command 1:\n");
    i = 0;
    while (data->cmd1[i])
    {
        printf("  cmd1[%d]: %s\n", i, data->cmd1[i]);
        i++;
    }

    printf("Command 2:\n");
    i = 0;
    while (data->cmd2[i])
    {
        printf("  cmd2[%d]: %s\n", i, data->cmd2[i]);
        i++;
    }
}

void	take_data(char **av, t_pipex *data)
{
	data->file1 = ft_strdup(av[1]);
	if (!data->file1)
		error_data(data, "ALLOCATION ERROR\n");
	data->file2 = ft_strdup(av[4]);
	if (!data->file2)
		error_data(data, "ALLOCATION ERROR\n");
	take_data_util(av, data);
}

void	take_data_util(char **av, t_pipex *data)
{
	char	*temp;
	
	data->cmd1 = ft_split(av[2], ' ');
	if (!data->cmd1)
		error_data(data, "ALLOCATION ERROR\n");
	temp = ft_strdup(data->cmd1[0]);
	free(data->cmd1[0]);
	data->cmd1[0] = ft_strjoin("/bin/", temp);
	free(temp);
	data->cmd2 = ft_split(av[3], ' ');
	if (!data->cmd2)
		error_data(data, "ALLOCATION ERROR\n");
	temp = ft_strdup(data->cmd2[0]);
	free(data->cmd2[0]);
	data->cmd2[0] = ft_strjoin("/bin/", temp);
	free(temp);
}

int main(int ac, char **av, char **envp)
{
	t_pipex	*data;
	(void)envp;

	if (ac != 5)
	{
		error_message("INCORRECT NUMBER OF ARGUMENTS\n");
		exit(1);
	}
	data = malloc(sizeof(t_pipex));
	if (!data)
	{
		error_message("ALLOCATION ERROR\n");
		exit(1);
	}
	take_data(av, data);
	check_args(data);
	pipex(data, envp);
	close(data->fd[0]);
	close(data->fd[1]);
	free_data(data);

	return (0);
}
