/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:34:39 by sucho             #+#    #+#             */
/*   Updated: 2023/08/11 17:49:44 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void	print_ant(t_path_len *elements, t_graph *paths)
{
	(void)paths;
	for(int i = 0; i < paths->num_paths; i++)
		printf("elements - value: %d\t index:%d\tnum_ants:%d\n", \
			elements[i].value, elements[i].index, elements[i].num_ants);

	int value = elements[0].value;
	int num_ants = elements[0].num_ants;
	int *path = paths->paths[0];

	int array[value];
	ft_memset(&array, 0, sizeof(array));
	int loop = num_ants + value;

	for (int i = 0; i < loop; i++)
	{

	}
}
