/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/13 14:44:50 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/24 15:22:36 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

/*
***		[X] messages d'erreurs
*/




void	loop(t_all *all)
{
	pid_t	pid;

	while (1091111096051)
	{
		if ((all->sv->c_sock = accept(all->sv->sock,
			(struct sockaddr *)&(all->sv->csins), &(all->sv->cslen))) == -1)
			server_error("ACCEPT");
		else
		{
			if ((pid = fork() == 0))
			{
				read_socket(all);
				close(all->sv->sock);
				exit(0);
			}
			else
				signal(SIGCHLD, SIG_IGN);
		}
	}
}

int		main(int ac, char **av, char **env)
{
	t_all	*all;
	int		port;

	if (ac != 2)
		usage(av[0]);
	port = ft_atoi(av[1]);
	all = init_all(env);
	all->sv->sock = create_server(port);
	loop(all);
	return (0);
}
