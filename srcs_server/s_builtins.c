/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleli42 <sleli42@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 22:19:02 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/22 12:30:10 by sleli42          ###   ########.fr       */
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
			send(c_sock, "~> SUCCESS\n", 12, 0);
			return (1);
		}
		i++;
	}
	send(c_sock, "~> ERROR\n", 10, 0);
	return (0);
}

void	display_pwd(char *cmd, int c_sock)
{
	char	*pwd;
	char	*buff;

	(void)cmd;
	buff = NULL;
	pwd = getcwd(buff, 42);
	send(c_sock, pwd, ft_strlen(pwd), 0);
	send(c_sock, "\n", 1, 0);
	ft_strdel(&pwd);
}

void	goto_directory(char *cmd, int c_sock)
{
	(void)c_sock;
	if (access(cmd, F_OK) == 0)
	{
		if (chdir(cmd) == -1)
			server_error("DIR");
	}
}

void	stop_connect(char *cmd, int c_sock)
{
	(void)cmd;
	write(0, "Bye bye!\n", 9);
	close(c_sock);
	exit(0);
}
