/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 21:52:58 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/16 22:27:34 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void	server_error(char *err)
{
	if (ft_strcmp(err, "ACCEPT") == 0)
		ft_putstr("accept() failed!\n");
	if (ft_strcmp(err, "GETPROTOBYNAME") == 0)
		ft_putstr("[server] getprotobyname() failed!\n");
	if (ft_strcmp(err, "BIND") == 0)
		ft_putstr("bind() failed!\n");
	if (ft_strcmp(err, "DIR") == 0)
		ft_putstr("cd <directory> failed!\n");
	exit(1);
}
