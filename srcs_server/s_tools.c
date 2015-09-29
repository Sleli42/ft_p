/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 22:21:53 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/29 12:36:25 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

//ssize_t recv(int s, void *buf, ssize_t len, int flags);

void	display_return_and_explanation(char *err, int sock2write, int msg, int spec)
{
	char	*buff;

	buff = NULL;
	if (spec == 'd')
	{
		buff = ft_strjoin("~> ERROR <", err);
		buff = ft_strjoin(buff, "> bad directory.. [`KO`]\n");
		send(sock2write, buff, ft_strlen(buff), 0);
		ft_strdel(&buff);
	}
	else if (spec == 'f')
	{
		buff = ft_strjoin("~> ERROR <", err);
		buff = ft_strjoin(buff, ">  is not a valid file.. [`KO`]\n");
		send(sock2write, buff, ft_strlen(buff), 0);
		ft_strdel(&buff);
	}
	else if (msg == 0 && spec == -1)
	{
		buff = ft_strjoin("~> ERROR '", err);
		buff = ft_strjoin(buff, "' command not found.. [`KO`]\n");
		send(sock2write, buff, ft_strlen(buff), 0);
		ft_strdel(&buff);
	}
	else if (msg == 1 && spec == -1)
	{
		buff = ft_strjoin("~> SUCCESS '", err);
		buff = ft_strjoin(buff, "'\t [`OK`]\n");
		send(sock2write, buff, ft_strlen(buff), 0);
	}
}

void	read_socket(t_all *all)
{
	int		r;
	char	buff[MAX_SIZE];

	ft_memset(buff, 0, ft_strlen(buff));
	while ((r = recv(all->sv->c_sock, buff, MAX_SIZE - 1, 0)) > 0)
	{
		buff[r] = 0;
		if (buff[0] == 0)
			send(all->sv->c_sock, "\0", 1, 0);
		else
		{
			if (try_builtins(all, buff) == 0)
				try_exec(all, buff);
		}
	}
}

// void	goto_dir(t_all *all)
// {
// 	char	*buff;

// 	buff = NULL;
// 	all->oldpwd = getcwd(buff, 42);
// 	all->oldpwd = ft_strjoin(all->oldpwd, "/");
// 	all->cmd = ft_strdup(all->cmd + 3);
// 	if (all->cmd[0] == '\0')
// 		all->cmd = ft_strdup("/nfs/zfs-student-5/users/2014/lubaujar/");
// 	else if (all->cmd[0] == '-')
// 		all->cmd = ft_strdup(find_env_arg(all, "OLDPWD") + 7);
// 	if (access(all->cmd, F_OK) == 0)
// 	{
// 		if (chdir(all->cmd) == -1)
// 			error("DIR");
// 		update_oldpwd(all);
// 	}
// }

// void	update_oldpwd(t_all *all)
// {
// 	t_node	*nav;

// 	nav = all->env->head;
// 	if (nav)
// 	{
// 		while (nav)
// 		{
// 			if (ft_strncmp(nav->s, "OLDPWD", 6) == 0)
// 			{
// 				ft_strdel(&nav->s);
// 				nav->s = ft_strjoin("OLDPWD=", all->oldpwd);
// 				return ;
// 			}
// 			nav = nav->next;
// 		}
// 	}
// }
