/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 22:19:02 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/18 01:08:18 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int		try_builtins(char *cmd, int c_sock)
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
			built[i].f(cmd, c_sock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	display_pwd(char *cmd, int c_sock)
{
	char	*pwd;
	char	*buff;
	char	*ret;

	(void)cmd;
	buff = NULL;
	pwd = getcwd(buff, 42);
	buff = ft_strjoin(pwd, "\n");
	ret = ft_strjoin(buff, "~> SUCCESS");
	ft_strdel(&buff);
	write(c_sock, ret, ft_strlen(ret));
	ft_strdel(&ret);
}

void	goto_directory(char *cmd, int c_sock)
{
	if (access(cmd, F_OK) == 0)
	{
		if (chdir(cmd) == -1)
			server_error("DIR");
		write(c_sock, "~> SUCCESS", 10);
	}
}

void	stop_connect(char *cmd, int c_sock)
{
	(void)cmd;
	write(1, "Bye bye!\n", 9);
	close(c_sock);
	exit(1);
}
