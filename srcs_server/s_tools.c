/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 22:21:53 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/15 22:43:18 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void	read_socket(int	sock)
{
	char	buff[1021];
	int		r;

	while ((r = read(client_s, buff, 1020)) > 0)
	{
		buff[r] = '\0';
		try_builtins(buff);
	}
}
