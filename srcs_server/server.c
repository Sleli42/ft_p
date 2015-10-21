/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/13 14:44:50 by lubaujar          #+#    #+#             */
/*   Updated: 2015/10/21 13:24:51 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void	mini_read_sock(t_all *all);

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
				mini_read_sock(all);
				//read_socket(all);
				close(all->sv->sock);
				exit(0);
			}
			else
				signal(SIGCHLD, SIG_IGN);
		}
	}
}

void	mini_read_sock(t_all *all)
{
	int		r;
	char	buff[MAX_SIZE];

	ft_memset(buff, 0, ft_strlen(buff));
	while ((r = read(all->sv->c_sock, buff, MAX_SIZE - 1)) > 0)
	{
		buff[r] = '\0';
		// function display */
		printf("Received %d bytes : %s\n", (int)ft_strlen(buff) - 1, buff);
		if (buff[0] == 10)
			write(all->sv->c_sock, "\0", 1);
		else
		{
			if (try_builtins(all, buff) == 1)
				write(all->sv->c_sock, "~ SUCCESS\n", 10);
			else
				write(all->sv->c_sock, "~ ERROR\n", 8);
		 		//try_exec(all, buff);

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
	all = s_init_all(env);
	all->sv->sock = create_server(port);
	loop(all);
	return (0);
}
