/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 22:21:53 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/16 22:21:15 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void	read_socket(t_server *sv)
{
	int		r;

	while ((r = read(sv->c_sock, sv->cmd, 1020)) > 0)
	{
		sv->cmd[r] = 0;
		if (try_builtins(sv) == 1)
			write(sv->c_sock, "SUCCESS\0", 8);
		else
			write(sv->c_sock, "ERROR\0", 6);
	}
}
