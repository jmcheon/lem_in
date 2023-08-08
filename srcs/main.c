/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 02:02:52 by sucho             #+#    #+#             */
/*   Updated: 2023/08/08 19:32:32 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"


int main(void)
{

	t_parse *parse;

	parse = parsing();

	parse_result_print(parse);
	ft_putstr_fd("lem-in\n", STDOUT_FILENO);

	return (0);
}
