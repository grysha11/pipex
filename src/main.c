/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:26:34 by hzakharc          #+#    #+#             */
/*   Updated: 2024/08/19 17:28:26 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_lst_size(t_list *lst)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = lst;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void	ft_lst_add_back(t_list **lst, t_list *new_node)
{
	t_list	*tmp;

	if (!new_node)
		return ;
	if (*lst == NULL)
		*lst = new_node;
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

t_list	*ft_list_new(char **value)
{
	t_list	*head;

	head = malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	head->value = value;
	head->next = NULL;
	return (head);
}

void	take_data_util(t_pipex *data, char **av, int ac)
{
	data->file1 = ft_strdup(av[1]);
	if (!data->file1)
		error_data(data, "ALLOCATION ERROR\n");
	data->file2 = ft_strdup(av[ac - 1]);
	if (!data->file2)
		error_data(data, "ALLOCATION ERROR\n");
}

void	take_data_util2(char **av, t_pipex *data)
{
	t_list	*temp;
	int		i;
	char	*tempstr;

	temp = data->cmd;
	i = 2;
	while (temp != NULL)
	{
		temp->value = ft_split(av[i], ' ');
		if (!temp->value)
			error_data(data, "ALLOCATION FAILED\n");
		tempstr = ft_strdup(temp->value[0]);
		free(temp->value[0]);
		temp->value[0] = ft_strjoin("/bin/", tempstr);
		free(tempstr);
		temp = temp->next;
		i++;
	}
}

void	take_data(t_pipex *data, char **av, int ac)
{
	t_list	*temp;
	t_list	*temp2;
	int		i;

	take_data_util(data, av, ac);
	data->cmd = ft_list_new(NULL);
	temp = data->cmd;
	i = 2;
	while (i < ac - 2)
	{
		temp2 = ft_list_new(NULL);
		ft_lst_add_back(&temp, temp2);
		temp = temp->next;
		i++;
	}
	take_data_util2(av, data);
}

void	exec_cmd(int fd[], t_list *cmd, t_pipex *data, char **envp)
{
	int	pid;
	int	pipefd[2];
	
	pid = fork();
	pipe(pipefd);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(fd[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		execve(cmd->value[0], cmd->value, envp);
		error_data(data, "Error: Unknown command\n");
		exit(1);
	}
	waitpid(pid, NULL, 0);
}

void	pipex(char **envp, t_pipex *data)
{
	t_list	*tmp;
	int	fd[2];

	tmp = data->cmd;
	fd[0] = open(data->file1, O_RDONLY);
	if (fd[0] < 0)
		error_data(data, "COULDN'T OPEN INFILE\n");
	fd[1] = open(data->file2, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd[1] < 0)
		error_data(data, "COULDN'T OPEN OUTFILe\n");
	while (tmp)
	{
		exec_cmd(fd, tmp, data, envp);
		tmp = tmp->next;
	}
	free_data(data);
}

void	print_list(t_list *lst)
{
	for (t_list *temp = lst; temp; temp = temp->next)
		for(int i = 0; temp->value[i]; i++)
			printf("%s\n", temp->value[i]);
}
int	main(int ac, char **av, char **envp)
{
	t_pipex	*data;
	(void)envp;

	if (ac < 5)
	{
		error_message("INCORRECT AMOUNT OF ARGUMENTS\n");
		return (1);
	}
	data = malloc(sizeof(t_pipex));
	if (!data)
	{
		error_message("ALLOCATION ERROR\n");
		return (1);
	}
	take_data(data, av, ac);
	// print_list(data->cmd);
	// printf("%s\n", data->file1);
	// printf("%s\n", data->file2);
	pipex(envp, data);
	return (0);
}

