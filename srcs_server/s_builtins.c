/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 22:19:02 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/22 23:23:15 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int		try_builtins(t_all *all, char *cmd)
{
	int						i;
	static const t_action	built[] =

	{{"pwd", display_pwd},
	{"cd", goto_directory},
	{"quit", stop_connect}};
	i = 0;
	while (i < 3)
	{
		if (ft_strncmp(cmd, built[i].action_name,
			ft_strlen(built[i].action_name)) == 0)
		{
			built[i].f(all, cmd);
			return (1);
		}
		i++;
	}
	return (0);
}

void	display_pwd(t_all *all, char *cmd)
{
	char	*pwd;
	char	*buff;

	(void)cmd;
	buff = NULL;
	pwd = getcwd(buff, 42);
	pwd = ft_strjoin(pwd, "\n");
	send(all->sv->c_sock, pwd, ft_strlen(pwd), 0);
	display_return_and_explanation(cmd, all->sv->c_sock, 0);
	ft_strdel(&pwd);
}

void	goto_directory(t_all *all, char *cmd)
{
	char	*buff;

	buff = NULL;
	cmd = ft_strdup(cmd + 3);
	if (access(cmd, F_OK) == 0)
	{
		if (chdir(cmd) == -1)
			server_error("DIR");
		else
		{
			if (ft_strlen(getcwd(buff, 42)) < ft_strlen(all->env->lowest_pwd))
			{
				display_return_and_explanation(cmd, all->sv->c_sock, 0);
				chdir(all->env->lowest_pwd);
			}
			display_return_and_explanation(cmd, all->sv->c_sock, 1);
		}
		ft_strdel(&cmd);
	}
	else
		display_return_and_explanation(cmd, all->sv->c_sock, 0);
}

void	stop_connect(t_all *all, char *cmd)
{
	(void)cmd;
	write(0, "Bye bye!\n", 9);
	close(all->sv->c_sock);
	exit(0);
}
