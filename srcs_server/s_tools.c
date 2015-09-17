/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 22:21:53 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/18 01:09:25 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void	read_socket(t_server *sv)
{
	int		pid;
	char	*buff;

	buff = NULL;
	if ((pid = fork()) == -1)
		server_error("FORK");
	else if (pid == 0)
	{
		while (get_next_line(sv->c_sock, &buff) > 0)
		{
			if (ft_strlen(buff) <= 0)
				write(sv->c_sock, "\0", 1);
			else
			{
				if (try_builtins(buff, sv->c_sock == 0)
					|| try_exec(sv, buff) == 0)
						write(sv->c_sock, "~> ERROR", 8);
			}
		}
	}
	else
		wait(NULL);
}
