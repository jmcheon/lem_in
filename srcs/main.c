/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 02:02:52 by sucho             #+#    #+#             */
/*   Updated: 2023/08/07 07:40:30 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int main(void)
{
	char buf[1024];

	if (!ft_isdigit(get_next_line(STDIN_FILENO)[0]))
	{
		ft_putstr_fd("Usage: ./lem-in < [filename]\n", STDOUT_FILENO);
		exit(0);
	}

	ft_putstr_fd("lem-in\n", STDOUT_FILENO);

	return 0;
}
