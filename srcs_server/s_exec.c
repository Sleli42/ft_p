/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/17 21:14:36 by lubaujar          #+#    #+#             */
/*   Updated: 2015/10/26 15:12:16 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int		try_exec(t_all *all, char *cmd)
{
	char	**argv_bin;
	//int		fd[2];

	cmd = ft_epur_str(cmd);
	//printf("|%s|\n", cmd);
	argv_bin = ft_strsplit(cmd, ' ');
	// pipe(fd);
	// close(fd[0]);
	// dup2(fd[1], 1);
	// close(1);
	//dup2(all->sv->c_sock, 1);
	if (exec_right_binary(all, argv_bin) == 1)
	{
		// close(1);
		//dup2(1, STDOUT_FILENO);
		del_array(&argv_bin);
		return (1);
		//display_return_and_explanation(cmd, all->sv->c_sock, 1, -1);
	}
	del_array(&argv_bin);
	// close(fd[1]);
	// else
	// {
	// 	// close(1);
	// 	// dup2(1, STDOUT_FILENO);
	// 	return (0);
	// 	//display_return_and_explanation(cmd, all->sv->c_sock, 0, -1);
	// }
	return (0);
}

int		good_access(char *bin)
{
	if (access(bin, F_OK) == 0)
		if (access(bin, X_OK) == 0)
			return (1);
	return (0);
}

char	*create_path(char *path, char *bin)
{
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	tmp = ft_strjoin(tmp, bin);
	return (tmp);
}

int		exec_right_binary(t_all *all, char **argv_bin)
{
	int		ct;
	char	*bin_tmp;

	ct = 0;
	bin_tmp = NULL;
	while (all->env->path2exec[ct])
	{
		bin_tmp = create_path(all->env->path2exec[ct], argv_bin[0]);
		if (good_access(bin_tmp))
		{
			exec_binary(bin_tmp, argv_bin, all->env->dupenv, all->sv->c_sock);
			//dup2(1, all->sv->c_sock);
			return (1);
		}
		ft_strdel(&bin_tmp);
		ct++;
	}
	return (0);
}


void	exec_binary(char *bin, char **argv_bin, char **env, int sock)
{
	int		buff;
	pid_t	pid;
	//int		fd[2];

	pid = fork();
	dup2(sock, 1);
	//pipe(fd);
	/*
	if ((pid = fork()) < 0)
		server_error("FORK");
	if (pid == 0)
	{
		close(fd[0]);
		close(fd[1]);
		wait(buff);
	}
	else
	{
		close(fd[0]);
		dup2();
	}
	*/
	if (pid == -1)
		server_error("FORK");
	if (pid == 0)
	{
		if (execve(bin, argv_bin, env) == -1)
			server_error("EXECVE");
		exit(0);
	}
	if (pid > 0)
		waitpid(pid, &buff, 0);
}
