/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/13 14:44:50 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/22 22:15:01 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int		main(int ac, char **av)
{
	int	port;
	int	sock;

	if (ac != 3)
		usage(av[1]);
	port = ft_atoi(av[2]);
	sock = create_client(av[1], port);
	write_socket(sock);
	return (0);
}
