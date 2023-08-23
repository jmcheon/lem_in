/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_dist_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:37:44 by sucho             #+#    #+#             */
/*   Updated: 2023/08/24 00:07:56 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-in.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_dist_multishot.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:19:38 by sucho             #+#    #+#             */
/*   Updated: 2023/08/23 16:13:04 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-in.h"

int		ants_find_dist_begin2(int *elements2, int num_paths, int num_ants)
{
	int ret;

	ret = 0;
	for (int i = 0; i < num_paths; i++)
	{
		int tmp = 0;
		for (int j = i + 1; j < num_paths; j++)
			tmp += (elements2[i] - elements2[j]);
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

void	ants_dist_fillin3(int *ant_dist, int *elements2, int paths_num, int dist_begin, int num_ants)
{
	int ants_to_dist = num_ants;
	int dist_len = paths_num - dist_begin;
	int ant_remainder;

	for (int i = paths_num - 1; i > dist_begin; i--)
	{
		int dist = elements2[dist_begin] - elements2[i];
		ant_dist[i] = dist;
		ants_to_dist -= dist;
	}
	ant_remainder = ants_to_dist % dist_len;
	for(int i= paths_num - 1; i >= dist_begin; i--)
	{
		ant_dist[i] += ants_to_dist / dist_len;
		// printf("ant_dist[%d]:%d\t%d\n",i, ant_dist[i], ant_num_temp / route.paths->num_paths);
		if (ant_remainder != 0)
		{
			ant_dist[i] += 1;
			ant_remainder--;
		}
	}
}
void	ants_dist_fillin2(int *ant_dist, t_path_len **elements, int paths_num, int dist_begin, int num_ants)
{
	int ants_to_dist = num_ants;
	int dist_len = paths_num - dist_begin;
	int ant_remainder;

	for (int i = paths_num - 1; i > dist_begin; i--)
	{
		int dist = elements[dist_begin]->value - elements[i]->value;
		ant_dist[i] = dist;
		ants_to_dist -= dist;
	}
	ant_remainder = ants_to_dist % dist_len;
	for(int i= paths_num - 1; i >= dist_begin; i--)
	{
		ant_dist[i] += ants_to_dist / dist_len;
		// printf("ant_dist[%d]:%d\t%d\n",i, ant_dist[i], ant_num_temp / route.paths->num_paths);
		if (ant_remainder != 0)
		{
			ant_dist[i] += 1;
			ant_remainder--;
		}
	}
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
	ants_dist_fillin3(ant_dist, elements, paths_num, dist_begin, route->num_ants);
	int result = elements[paths_num - 1] + ant_dist[paths_num -1];
	return (result);
}
