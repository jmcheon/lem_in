/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 02:02:52 by sucho             #+#    #+#             */
/*   Updated: 2023/08/09 02:21:03 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"


int main(void)
{

	t_parse *parse;
	t_graph_type* g;

	parse = parsing();

	parse_result_print(parse);
	g = parse_to_graph(parse);
	print_adj_list(g);
	ft_putstr_fd("lem-in\n", STDOUT_FILENO);

	return (0);
}
