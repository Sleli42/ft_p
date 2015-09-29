/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/17 21:14:36 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/29 12:43:30 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void	try_exec(t_all *all, char *cmd)
{
	char	**argv_bin;

	cmd = ft_epur_str(cmd);
	argv_bin = ft_strsplit(cmd, ' ');
	close(1);
	dup2(all->sv->c_sock, 1);
	if (exec_right_binary(all, argv_bin) == 1)
	{
		dup2(1, STDOUT_FILENO);
		del_array(&argv_bin);
		display_return_and_explanation(cmd, all->sv->c_sock, 1, -1);
	}
	else
	{
		// dup2(1, STDOUT_FILENO);
		display_return_and_explanation(cmd, all->sv->c_sock, 0, -1);
	}
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
			exec_binary(bin_tmp, argv_bin, all->env->dupenv);
			return (1);
		}
		ft_strdel(&bin_tmp);
		ct++;
	}
	return (0);
}

void	exec_binary(char *bin, char **argv_bin, char **env)
{
	int		buff;
	pid_t	pid;

	pid = fork();
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
