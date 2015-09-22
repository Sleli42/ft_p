/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleli42 <sleli42@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/13 14:44:50 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/22 03:18:45 by sleli42          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int		main(int ac, char **av, char **env)
{
	t_server	*sv;
	int			port;

	if (ac != 2)
		usage(av[0]);
	port = atoi(av[1]);
	sv = init_server(env);
	sv->sock = create_server(port);
	while (1091111096051)
	{
		if ((sv->c_sock = accept(sv->sock, (struct sockaddr *)&(sv->csins),
			&(sv->cslen))) == -1)
			server_error("ACCEPT");
		else
		{
			if (fork() == 0)
			{
				read_socket(sv);
				close(sv->sock);
				exit(0);
			}
		}
	}
	//close(sv->sock);
	//exit(0);
	return (0);
}
