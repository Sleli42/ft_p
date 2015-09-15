/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 23:50:21 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/16 00:46:46 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void	write_socket(int sock)
{
	char	*buff;

	buff = NULL;
	write(1, "$: ", 3);
	while (get_next_line(0, &buff) > 0)
	{
		write(1, "$: ", 3);
		write(sock, buff, ft_strlen(buff));
		if (ft_strcmp(buff, "quit") == 0)
			close_and_exit(sock);
	}
}

void	close_and_exit(int sock)
{
	write(1, "quit\n", 5);
	close(sock);
	exit(1);
}
