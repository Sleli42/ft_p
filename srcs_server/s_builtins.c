/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 22:19:02 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/16 00:41:28 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void	try_builtins(t_server *sv)
{
	int						i;
	static const t_action	built[] =

	{{"pwd", display_pwd},
	{"cd", goto_directory},
	{"quit", stop_connect}};
	i = 0;
	while (i < 3)
	{
		if (ft_strncmp(sv->cmd, built[i].action_name,
			ft_strlen(built[i].action_name)) == 0)
			built[i].f(sv);
		i++;

	}
}

void	display_pwd(t_server *sv)
{
	char	*pwd;
	char	*buff;

	(void)sv;
	buff = NULL;
	pwd = getcwd(buff, 42);
	dup2(sv->c_sock, 1);
	close(1);
	ft_putendl(pwd);
}

void	goto_directory(t_server *sv)
{
	if (access(sv->cmd, F_OK) == 0)
	{
		if (chdir(sv->cmd) == -1)
			server_error("DIR");
	}
}

void	stop_connect(t_server *sv)
{
	write(1, "Bye bye!\n", 9);
	close(sv->sock);
	close(sv->c_sock);
	exit(1);
}
