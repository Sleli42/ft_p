/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/13 14:44:50 by lubaujar          #+#    #+#             */
/*   Updated: 2015/10/21 13:29:46 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void	mini_write_sock(int sock);

int		main(int ac, char **av)
{
	int	port;
	int	sock;
	t_all	*all;

	if (ac != 3)
		usage(av[1]);
	port = ft_atoi(av[2]);
	sock = create_client(av[1], port);
	all = c_init_all();
	//write_socket(all, sock);
	mini_write_sock(sock);
	return (0);
}

void	read_return(int sock)
{
	int		r;
	char	buff[MAX_SIZE];

	ft_memset(buff, 0, ft_strlen(buff));
	while ((r = read(sock, buff, MAX_SIZE - 1)) > 0)
	{
		buff[r] = '\0';
		write(1, buff, ft_strlen(buff));
		//write(1, &buff[0], 1);
		if (buff[0] == '~' || buff[0] == '\0')
			return ;
	}
}

void	mini_write_sock(int sock)
{
	int		r;
	char	buff[MAX_SIZE];

	ft_memset(buff, 0, ft_strlen(buff));
	while (1)
	{
		write(1, "$: ", 3);
		while ((r = read(0, buff, MAX_SIZE - 1)) > 0)
		{
			buff[r] = '\0';
			write(sock, buff, ft_strlen(buff));
			if (ft_strcmp(buff, "quit\n") == 0)
				close_and_exit(sock);
			break;
		}
		read_return(sock);
	}
}
