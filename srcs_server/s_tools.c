/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 22:21:53 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/17 19:30:54 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void	read_socket(t_server *sv)
{
	char	*buff;

	buff = NULL;
	while (get_next_line(sv->c_sock, &buff) > 0)
	{
		// printf("|%s|\n", buff);
		// printf("len: %zu\n", ft_strlen(buff));
		if (try_builtins(buff, sv->c_sock) != 1)
		{
			if (ft_strlen(buff) > 0)
				write(sv->c_sock, "~> ERROR", 8);
			else
				write(sv->c_sock, "\0", 1);
		}
	}
}
