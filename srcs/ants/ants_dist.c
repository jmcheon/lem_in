/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_dist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 07:19:48 by sucho             #+#    #+#             */
/*   Updated: 2023/08/25 16:58:39 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-in.h"

int		ft_intlen(int *s)
{
	int i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ants_dist_fillin(int *ant_dist, t_path_len **elements, t_route route, t_paths *paths)
{
	int ants_to_dist = route.num_ants;
	int dist_len = paths->num_paths - paths->dist_begin;
	int ant_remainder;

	for (int i = paths->num_paths - 1; i > paths->dist_begin; i--)
	{
		int dist = elements[paths->dist_begin]->value - elements[i]->value;
		ant_dist[i] = dist;
		ants_to_dist -= dist;
	}
	ant_remainder = ants_to_dist % dist_len;
	for(int i = paths->num_paths - 1; i >= paths->dist_begin; i--)
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

int		ants_find_dist_begin(t_path_len **elements, int num_paths, int num_ants)
{
	int ret;

	ret = 0;
	for (int i = 0; i < num_paths; i++)
	{
		int tmp = 0;
		for (int j = i + 1; j < num_paths; j++)
			tmp += (elements[i]->value - elements[j]->value);
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

void	ants_setup_elements(t_path_len **elements, t_paths *paths)
{
	t_list *paths_head;
	t_vertex_list *onepath_head;
	int i;
	// int j;

	paths_head = paths->paths;
	// onepath_head = (t_vertex_list*)paths_head->content;
	i = 0;
	while (paths_head != NULL)
	{
		elements[i]->index = i;
		// j = 0;
		onepath_head = (t_vertex_list*)paths_head->content;

		// while(onepath_head != NULL)
		// {
		// 	j++;
		// 	// printf("vertex:%d\n", onepath_head->vertex);
		// 	onepath_head = onepath_head->next;
		// }
		// printf("j:%d\n",j);
		elements[i]->value = onepath_head->prev->length; // start and end
		elements[i]->num_ants = 0;
		i++;
		paths_head = paths_head->next;
	}

}

t_path_len	**ants_init_elements(t_paths *paths)
{
	t_path_len **ret;

	ret = (t_path_len**)malloc(sizeof(t_path_len*) * (paths->num_paths + 1));
	int i = 0;
	while (i < paths->num_paths)
	{
		ret[i] = (t_path_len*)malloc(sizeof(t_path_len));
		i++;
	}
	ret[i] = NULL;
	ants_setup_elements(ret, paths);

	return (ret);
}

t_path_len	**ants_distribute(t_route route, t_paths *paths)
{
	// printf("num_paths:%d\tant_num:%d\n", route.paths->num_paths, route.num_ants);

	t_path_len **elements;

	// t_list *paths_head;
	// t_vertex_list *onepath_head;

	elements = ants_init_elements(paths);
	(void)	route;


    // printf("Original array:\n");
    // for (int i = 0; i < paths->num_paths; i++) {
    //     printf("%d ", elements[i]->value);
    // }
    // printf("\n");

	quicksort(elements, 0, paths->num_paths - 1);

    // // printf("Sorted array in descending order:\n");
    // // for (int i = 0; i < route.paths->num_paths; i++) {
    // //     printf("%d (Index: %d) ", elements[i]->value, elements[i]->index);
    // // }
	// // printf("\n");

	// // int dist_begin = 0;
	// // for (int i = 0; i < route.paths->num_paths; i++)
	// // {
	// // 	int tmp = 0;
	// // 	for (int j = i + 1; j < route.paths->num_paths; j++)
	// // 		tmp += (elements[i]->value - elements[j]->value);
	// // 	// printf("tmp:%d\n", tmp);
	// // 	// printf("tmp2:%d \n", tmp + (route.paths->num_paths - i));
	// // 	if (tmp + (route.paths->num_paths - i) <= route.num_ants)
	// // 	{
	// // 		dist_begin = i;
	// // 		break;
	// // 	}
	// // }
	// int dist_begin;
	// dist_begin = paths->dist_begin;
	// //printf("distribution begins from here: [%d]\n", dist_begin);

	// int ant_num_temp = route.num_ants;
	// int dist_len = route.paths->num_paths - dist_begin;

	int ant_dist[paths->num_paths];
	// int ant_dist[route.paths->num_paths];
	ft_memset(&ant_dist, 0, sizeof(ant_dist));

	// // printf("%d\n", dist_len);

	// for (int i = paths->num_paths - 1; i > paths->dist_begin; i--)
	// {
	// 	int dist = elements[i - 1]->value - elements[i]->value;
	// 	ant_dist[i] += dist;
	// 	ant_num_temp -= dist;
	// }

	ants_dist_fillin(ant_dist, elements, route, paths);
	// // printf("ant_num_temp:[%d]\n",ant_num_temp);

	// // // int dist_len = route.paths->num_paths - dist_begin;
	// // int ant_remainder = route.num_ants % dist_len;
	// // // printf("ant_num_temp:%d\tdist_len:%d\ttmp:%d\n", ant_num_temp, dist_len, ant_remainder);
	// // for(int i= route.paths->num_paths - 1; i >= dist_begin; i--)
	// // {
	// // 	ant_dist[i] += route.num_ants / dist_len;
	// // 	// printf("ant_dist[%d]:%d\t%d\n",i, ant_dist[i], ant_num_temp / route.paths->num_paths);
	// // 	if (ant_remainder != 0)
	// // 	{
	// // 		ant_dist[i] += 1;
	// // 		ant_remainder--;
	// // 	}
	// // }

	// // // printf("=========================\n");

	for(int i = 0; i < paths->num_paths; i++)
		elements[i]->num_ants = ant_dist[i];
	return (elements);
}
