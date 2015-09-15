/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 21:53:13 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/15 22:43:18 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void	client_error(char *err)
{
	if (ft_strcmp(err, "ACCEPT") == 0)
		ft_putstr("accept() failed!\n");
	if (ft_strcmp(err, "GETPROTOBYNAME") == 0)
		ft_putstr("[client] getprotobyname() failed!\n");
	exit(1);
}
