/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_dist_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:37:44 by sucho             #+#    #+#             */
/*   Updated: 2023/08/23 16:39:08 by sucho            ###   ########.fr       */
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

void	ants_setup_elements2(t_path_len **elements, t_list *paths)
{
	t_list *paths_head;
	t_list *onepath_head;
	int i;
	int j;

	paths_head = paths;
	// onepath_head = (t_vertex_list*)paths_head->content;
	i = 0;
	while (paths_head != NULL)
	{
		elements[i]->index = i;
		j = 0;
		onepath_head = (t_list*)paths_head->content;

		while(onepath_head != NULL)
		{
			j++;
			// printf("vertex:%d\n", onepath_head->vertex);
			onepath_head = onepath_head->next;
		}
		// printf("j:%d\n",j);
		elements[i]->value = j; // start and end
		elements[i]->num_ants = 0;
		i++;
		paths_head = paths_head->next;
	}

}

t_path_len	**ants_init_elements2(t_list *paths, int num_paths)
{
	t_path_len **ret;

	ret = (t_path_len**)malloc(sizeof(t_path_len*) * (num_paths + 1));
	int i = 0;
	while (i < num_paths)
	{
		ret[i] = (t_path_len*)malloc(sizeof(t_path_len));
		i++;
	}
	ret[i] = NULL;
	ants_setup_elements2(ret, paths);

	return (ret);
}

int	ants_check_loop_len(t_route *route, t_list *paths)
{
	t_path_len **elements;

	// (void)route;
	int paths_num = ft_lstsize(paths);
	// printf("paths_num: %d\n", paths_num);

	elements = ants_init_elements2(paths, paths_num);

	// (void)elements;

    // printf("Original array:\n");
    // for (int i = 0; i < paths_num; i++) {
    //     printf("%d ", elements[i]->value);
    // }
    // printf("\n");
	quicksort(elements, 0, paths_num - 1);
	// printf("Sorted array in descending order:\n");
    // for (int i = 0; i < paths_num; i++) {
    //     printf("%d (Index: %d) ", elements[i]->value, elements[i]->index);
    // }
	// printf("\n");


	//dist_begin in route
	int dist_begin;
	dist_begin = ants_find_dist_begin(elements, \
								paths_num, route->num_ants);
	// printf("distribution begins from here: [%d]\n", dist_begin);
	int ant_dist[paths_num];
	ft_memset(&ant_dist, 0, sizeof(ant_dist));
	ants_dist_fillin2(ant_dist, elements, paths_num, dist_begin, route->num_ants);
	for(int i = 0; i < paths_num; i++)
		elements[i]->num_ants = ant_dist[i];
	// printf("=======================\n");
	// for(int i = 0; elements[i] != NULL; i++)
	// 	printf("value:%d\tindex:%d\t\tnum_ants:%d\n",elements[i]->value, elements[i]->index, elements[i]->num_ants);

	// printf("=======================\n");

	return (elements[paths_num - 1]->value + elements[paths_num -1]->num_ants);
}
