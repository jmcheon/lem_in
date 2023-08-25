/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_dist_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:19:38 by sucho             #+#    #+#             */
/*   Updated: 2023/08/25 16:54:43 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-in.h"

int		ants_find_dist_begin2(int *elements, int num_paths, int num_ants)
{
	int ret;

	ret = 0;
	for (int i = 0; i < num_paths; i++)
	{
		int tmp = 0;
		for (int j = i + 1; j < num_paths; j++)
			tmp += (elements[i] - elements[j]);
		// printf("tmp:%d\n", tmp);
		// printf("tmp2:%d \n", tmp + (route.paths->num_paths - i));
		if (tmp + (num_paths - i) <= num_ants)
		{
			ret = i;
			break;
		}
	}
	return (ret);
}

int	ants_dist_find_result(int *ant_dist, int *elements, int paths_num, int dist_begin, int num_ants)
{
	int dist_len = paths_num - dist_begin;
	int ants_remainder;
	int ants_div;

	for (int i = paths_num - 1; i > dist_begin; i--)
	{
		ant_dist[i] = elements[dist_begin] - elements[i];
		num_ants -= ant_dist[i];
	}
	ants_remainder = num_ants % dist_len;
	ants_div = num_ants / dist_len;
	return (elements[paths_num -1] + ant_dist[paths_num - 1] + ants_div + (ants_remainder > 0 ? 1 : 0));
}

void	ants_setup_elements_array(int *elements2, t_list *paths)
{
	t_list *paths_head;
	t_vertex_list *onepath_head;
	int i;

	paths_head = paths;
	i = 0;
	while (paths_head != NULL)
	{
		onepath_head = (t_vertex_list*)paths_head->content;
		elements2[i] = onepath_head->prev->length; // start and end

		i++;
		paths_head = paths_head->next;
	}

}


int	ants_check_loop_len(t_route *route, t_paths *paths)
{
	int	elements[paths->num_paths];
	int paths_num = ft_lstsize((t_list *)paths->paths);
	int dist_begin;
	paths->num_paths = paths_num;

	ants_setup_elements_array(elements, paths->paths);
	quicksort_int_array(elements, 0, paths_num - 1);

	dist_begin = ants_find_dist_begin2(elements, \
								paths_num, route->num_ants);
	paths->dist_begin = dist_begin;
	int ant_dist[paths_num];
	ft_memset(&ant_dist, 0, sizeof(ant_dist));
	return (ants_dist_find_result(ant_dist, elements, paths_num, dist_begin, route->num_ants));
}
