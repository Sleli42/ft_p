/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/17 21:54:48 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/21 12:06:38 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void	display_tab(char **tab)
{
	int		i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			ft_putendl(tab[i++]);
	}
}
