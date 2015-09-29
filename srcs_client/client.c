/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/13 14:44:50 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/29 21:46:09 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int		main(int ac, char **av)
{
	int	port;
	int	sock;
	t_all	*all;

	if (ac != 3)
		usage(av[1]);
	port = ft_atoi(av[2]);
	sock = create_client(av[1], port);
	all = init_all();
	write_socket(sock);
	return (0);
}
