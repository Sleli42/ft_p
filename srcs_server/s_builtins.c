/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 22:19:02 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/15 22:43:20 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void	try_builtins(char *buff)
{
	int						i;
	static const t_action	built[] =

	{{"pwd", display_pwd},
	{"cd", goto_directory},
	{"quit", stop_connect}};
	i = 0;
	while (i < 3)
	{
		if (ft_strncmp(buff, built.action_name[i],
			ft_strlen(built.action_name[i])) == 0)
			built[i].f(buff);
		i++;

	}
}

void	display_pwd(char *s)
{
	char	*pwd;
	char	*buff;

	(void)s;
	buff = NULL;
	pwd = getcwd(buff, 42);
	ft_putendl(pwd);
}

void	goto_directory(char *s)
{
	if (access(s, F_OK) == 0)
	{
		if (chdir(s) == -1)
			server_error("DIR");
	}
}

void	stop_connect(char *s)
{

}
